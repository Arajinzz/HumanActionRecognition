#include "videoanalysis.h"

/*
 * Class Pour des Differentes Manipulations dans un Video
 *
 * */

VideoAnalysis::VideoAnalysis(){

}

VideoAnalysis::VideoAnalysis(string path_video)
{
    this->path_video = path_video;
    LoadVideo();
}



//Charger la video dans un vecteur
void VideoAnalysis::LoadVideo(){

    cv::VideoCapture cap(path_video);
    cv::Mat frame;

    if(!cap.isOpened())
        throw "Chemin invalide";


    while(true){

        cap >> frame;

        //La fin du video
        if(frame.empty())
            break;

        Allframes.push_back(frame.clone());

    }

    cap.release();

}

//Sauvgarder Une Video
void VideoAnalysis::StoreVideo(vector<cv::Mat> frames, string savePath){

    if(frames.empty())
        return;

    cv::Mat _frame = frames[0];

    cv::VideoWriter outVideo(savePath,-1,30,cv::Size(_frame.cols,_frame.rows));

    for(cv:: Mat frame : frames){
        outVideo.write(frame);
    }

    outVideo.release();

}


//eliminer le bruit d'une frame
cv::Mat VideoAnalysis::NoiseElim(cv::Mat frame){


    cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
    cv::Mat structuringElement3x3 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3));
    //cv::Mat structuringElement5x5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
    //cv::Mat structuringElement7x7 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
    //cv::Mat structuringElement9x9 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9, 9));

    //cv::GaussianBlur(frameDiff, frameDiff, cv::Size(5, 5), 1/25);
    //cv::threshold(frameDiff, frameDiff, 100, 255, cv::THRESH_BINARY);

    cv::GaussianBlur(frame, frame, cv::Size(5, 5), 1/25);
    cv::threshold(frame, frame, 150, 255, cv::THRESH_BINARY);

    cv::dilate(frame, frame, structuringElement3x3);
    cv::erode(frame, frame, structuringElement3x3);


    return frame;

}

//Generer le MEI du Video
cv::Mat VideoAnalysis::GenerateMEI(int frameEnd){

    cv::Mat MEI;

    int counter = 1;

    bool b = false;
    bool Direction = isMoving(true);

    for (cv::Mat frame : Allframes) {

        frame = NoiseElim(frame).clone();

        //initialiser le MEI
        if (b == false) {
            MEI = frame.clone();
            b = true;
        }
        else {

            for (int i = 0; i < MEI.rows; i++) {
                for (int j = 0; j < MEI.cols; j++) {

                    if (frame.at<uint8_t>(i, j) >= 200) {
                        MEI.at<uint8_t>(i, j) = frame.at<uint8_t>(i, j);
                    }

                }
            }

        }


        MEI_V.push_back(MEI.clone());

        if (counter == frameEnd) break;
        counter++;

    }

    Original = MEI.clone();

    ImageAnalysis analyse(MEI);

    if (Direction)
        MEI = analyse.FlipImage().clone();

    ImageAnalysis tempAN(MEI);

    cv::Mat ShiftedMei = ShiftUpLeft(MEI, tempAN.findBounds(200)).clone();

    return ShiftedMei;

}

//Generer le MHI d'une Video
cv::Mat VideoAnalysis::GenerateMHI(int frameEnd, int tau, int variation){

    cv::Mat MHI;
    cv::Mat prevFrame;

    bool b = false;
    bool Direction = isMoving(true);

    int counter = 1;

    cv::Mat lastFrame;

    for (cv::Mat frame: Allframes) {

        frame = NoiseElim(frame).clone();

        //pour detecter les pixel qui ont mouvement
        cv::Mat frameDiff;

        //initialiser le MHI
        if (!b) {

            //cree une image noire
            MHI = frame.clone();
            cv::threshold(MHI, MHI, 0, 0, cv::THRESH_BINARY);
            b = true;
            prevFrame = frame.clone();

        }
        else {

            //detecter les pixels qui sont en mouvement
            cv::absdiff(frame, prevFrame, frameDiff);
            cv::Mat prevMHI = MHI.clone();

            for (int i = 0; i < MHI.rows; i++) {
                for (int j = 0; j < MHI.cols; j++) {

                    if (frameDiff.at<uint8_t>(i, j) >= 240) {
                        MHI.at<uint8_t>(i, j) = tau;
                    }
                    else {
                        MHI.at<uint8_t>(i, j) = max(0, prevMHI.at<uint8_t>(i, j) - variation);
                    }

                }
            }

            prevFrame = frame.clone();

        }

        MHI_V.push_back(MHI.clone());

        if (frameEnd == counter) {

            lastFrame = frame.clone();
            break;
        }

        lastFrame = frame.clone();

        counter++;

    } // end of while

    if(isMoving(false)){
        for (int i = 0; i < MHI.rows; i++) {
            for (int j = 0; j < MHI.cols; j++) {

                if(lastFrame.at<uint8_t>(i, j) != 0){
                    MHI.at<uint8_t>(i,j) = 255;
                }

            }
        }
    }

    Original = MHI.clone();

    ImageAnalysis analyse(MHI);

    if (Direction)
        MHI = analyse.FlipImage().clone();

    ImageAnalysis tempAN(MHI);

    cv::Mat ShiftedMhi = ShiftUpLeft(MHI, tempAN.findBounds(1));

    return ShiftedMhi;

}


//detecter si la personne dans la video est en mouvement
//checkingdirection pour verifier la direction de la personne dans la video
bool VideoAnalysis::isMoving(bool CheckingDirection) {

    cv::Mat frame1;
    cv::Mat frame2;

    cv::Point Center1;
    cv::Point Center2;

    frame1 = Allframes[0];
    frame1 = NoiseElim(frame1);

    frame2 = Allframes[9];
    frame2 = NoiseElim(frame2);

    Center1 = ImageAnalysis(frame1).GravityCenter(100);
    Center2 = ImageAnalysis(frame2).GravityCenter(100);

    if(CheckingDirection){
        if (Center1.y >= Center2.y || abs(Center1.y - Center2.y) < 10)
            return false;
        else
            return true;
    }else{
        if (abs(Center1.y - Center2.y) < 10)
            return false;
        else
            return true;
    }

}

//Pour Positionner MEI et MHI a une place c'est effective a la reconnaissance avec Tchiebychef
cv::Mat VideoAnalysis::ShiftUpLeft(cv::Mat frame, cv::Point *bounds) {

    frame = ImageAnalysis(frame).Shift(bounds, 0, bounds[0].x);
    bounds = ImageAnalysis(frame).findBounds(1);
    frame = ImageAnalysis(frame).Shift(bounds, 3, frame.cols - bounds[3].y - 1);

    return frame;

}


//centred MEI
cv::Mat VideoAnalysis::centredMEI(int frames) {

    cv::Mat centredMEI;

    cv::Point fixedPoint;
    cv::Point massCenter;
    cv::Point *bounds;

    bool b = false;

    bool Direction = isMoving(true);

    int counter = 1;

    for(cv::Mat frame : Allframes){

        frame = NoiseElim(frame).clone();

        massCenter = ImageAnalysis(frame).GravityCenter(100);
        bounds = ImageAnalysis(frame).findBounds(100);

        if (b == false) {

            centredMEI = frame.clone();

            fixedPoint.x = centredMEI.rows / 2;
            fixedPoint.y = centredMEI.cols / 2;

            centredMEI = ImageAnalysis(centredMEI).shiftedToPoint(bounds,fixedPoint, massCenter).clone();

            b = true;

        }
        else {

            frame = ImageAnalysis(frame).shiftedToPoint(bounds, fixedPoint, massCenter).clone();

            for (int i = 0; i < frame.rows; i++) {

                for (int j = 0; j < frame.cols; j++) {

                    if (frame.at<uint8_t>(i, j) != 0) {

                        centredMEI.at<uint8_t>(i, j) = frame.at<uint8_t>(i, j);

                    }

                }
            } // end first for

        }// end else

        if(frames == counter)
            break;

        counter++;

    }

    Original = centredMEI.clone();

    if (Direction)
        centredMEI = ImageAnalysis(centredMEI).FlipImage();

    //centredMEI = ShiftUpLeft(centredMEI,ImageAnalysis(centredMEI).findBounds(1));

    return centredMEI;

}

cv::Mat VideoAnalysis::centredMHI(int tau, int variation , int frames) {

    cv::Mat centredMHI;
    cv::Mat prevFrame;
    cv::Mat frameDiff;

    cv::Point fixedPoint;
    cv::Point massCenter;
    cv::Point *bounds;

    bool b = false;

    bool Direction = isMoving(true);

    int counter = 1;

    for(cv::Mat frame : Allframes){

        frame = NoiseElim(frame).clone();

        if (b == false) {
            centredMHI = frame.clone();

            fixedPoint.x = centredMHI.rows / 2;
            fixedPoint.y = centredMHI.cols / 2;

            cv::threshold(centredMHI,centredMHI,0,0,cv::THRESH_BINARY);

            prevFrame = frame.clone();

            b = true;
        }
        else {

            cv::Mat prevMHI = centredMHI.clone();

            massCenter = ImageAnalysis(frame).GravityCenter(1);
            //bounds = ImageAnalysis(frame).findBounds(1);
            //frame = ImageAnalysis(frame).shiftedToPoint(bounds, fixedPoint, massCenter);

            //massCenter = ImageAnalysis(prevFrame).GravityCenter(1);
            //bounds = ImageAnalysis(prevFrame).findBounds(1);
            //prevFrame = ImageAnalysis(prevFrame).shiftedToPoint(bounds, fixedPoint, massCenter);

            cv::absdiff(frame,prevFrame,frameDiff);

            //cv::Mat structuringElement3x3 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3));
            //cv::Mat structuringElement5x5 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5));
            //cv::Mat structuringElement7x7 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
            //cv::Mat structuringElement9x9 = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(9, 9));

            //cv::GaussianBlur(frameDiff, frameDiff, cv::Size(5, 5), 1/25);
            //cv::threshold(frameDiff, frameDiff, 100, 255, cv::THRESH_BINARY);

            //cv::dilate(frameDiff, frameDiff, structuringElement3x3);
            //cv::erode(frameDiff, frameDiff, structuringElement3x3);


            //massCenter = ImageAnalysis(frameDiff).GravityCenter(1);

            bounds = ImageAnalysis(frameDiff).findBounds(1);

            frameDiff = ImageAnalysis(frameDiff).shiftedToPoint(bounds, fixedPoint, massCenter);

            //bounds = ImageAnalysis(frameDiff).findBounds(1);

            for (int i = 0; i < frame.rows; i++) {

                for (int j = 0; j < frame.cols; j++) {

                    if (frameDiff.at<uint8_t>(i, j) != 0) {

                        centredMHI.at<uint8_t>(i, j) = 255;

                    }else{

                        centredMHI.at<uint8_t>(i, j) = max(0, prevMHI.at<uint8_t>(i, j) - variation);

                    }

                }
            } // end first for

            prevFrame = frame.clone();

        }// end else


        if(frames == counter)
            break;

        counter++;


    }

    Original = centredMHI.clone();

    if (Direction)
        centredMHI = ImageAnalysis(centredMHI).FlipImage();

    //centredMHI = ShiftUpLeft(centredMHI,ImageAnalysis(centredMHI).findBounds(1));

    return centredMHI;

}

