#include "imageanalysis.h"

/*
 * Class Avec des Different Operation
 * Sur Les Images
 * */

ImageAnalysis::ImageAnalysis(cv::Mat image)
{
    this->image = image.clone();
}

//Pour Trouver les Bounds de La sillhouette
cv::Point* ImageAnalysis::findBounds(int grayLevel) {

    int xUp, yUp, xBottom, yBottom, xTempUP, yTempUP, xTempBottom, yTempBottom;
    bool bUP = false;
    bool bBottom = false;
    cv::Point Up;
    cv::Point Bottom;

    // to find the highest and lowest point with white color
    for (int j = 0; j < image.cols; j++) {

        for (int i = 0; i < image.rows; i++) {

            if (image.at<uint8_t>(i, j) >= grayLevel) {
                xUp = i;
                yUp = j;
                if (!bUP) {
                    bUP = true;
                    xTempUP = xUp;
                    yTempUP = yUp;
                }
                else {

                    if (xUp < xTempUP) {
                        xTempUP = xUp;
                        yTempUP = yUp;
                    }

                }
            }

            if (image.at<uint8_t>(image.rows - 1 - i, j) >= grayLevel) {
                xBottom = image.rows - 1 - i;
                yBottom = j;
                if (!bBottom) {
                    bBottom = true;
                    xTempBottom = xBottom;
                    yTempBottom = yBottom;
                }
                else {

                    if (xBottom > xTempBottom) {
                        xTempBottom = xBottom;
                        yTempBottom = yBottom;
                    }

                }
            }

        }

    }

    int xRight, yRight, xLeft, yLeft, xTempRight, yTempRight, xTempLeft, yTempLeft;
    cv::Point Right, Left;
    bool bRight = false;
    bool bLeft = false;

    //find the right point and left
    for (int i = 0; i < image.rows; i++) {

        for (int j = 0; j < image.cols; j++) {

            if (image.at<uint8_t>(i, j) >= grayLevel) {
                xLeft = i;
                yLeft = j;
                if (!bLeft) {
                    bLeft = true;
                    xTempLeft = xLeft;
                    yTempLeft = yLeft;
                }
                else {

                    if (yLeft < yTempLeft) {
                        xTempLeft = xLeft;
                        yTempLeft = yLeft;
                    }

                }

            }

            if (image.at<uint8_t>(i, image.cols - 1 - j) >= grayLevel) {
                xRight = i;
                yRight = image.cols - 1 - j;
                if (!bRight) {
                    bRight = true;
                    xTempRight = xRight;
                    yTempRight = yRight;
                }
                else {

                    if (yRight > yTempRight) {
                        xTempRight = xRight;
                        yTempRight = yRight;
                    }

                }
            }

        }

    }


    Up.x = xTempUP;
    Up.y = yTempUP;

    Bottom.x = xTempBottom;
    Bottom.y = yTempBottom;

    Right.x = xTempRight;
    Right.y = yTempRight;

    Left.x = xTempLeft;
    Left.y = yTempLeft;

    cv::Point *bounds = new cv::Point[4];
    bounds[0].x = Up.x ;
    bounds[0].y = Left.y ;

    bounds[1].x = Up.x ;
    bounds[1].y = Right.y ;

    bounds[2].x = Bottom.x ;
    bounds[2].y = Left.y ;

    bounds[3].x = Bottom.x ;
    bounds[3].y = Right.y ;


    return bounds;

}

//Draw Rectangle pour les test
cv::Mat ImageAnalysis::drawRectangle(cv::Point *bounds) {

    cv::Mat temp = image.clone();

    //draw Ligne
    for (int i = bounds[0].y; i <= bounds[1].y; i++) {
        temp.at<uint8_t>(bounds[0].x, i) = 100;
    }
    for (int i = bounds[0].x; i <= bounds[2].x; i++) {
        temp.at<uint8_t>(i, bounds[0].y) = 100;
    }
    for (int i = bounds[2].y; i <= bounds[3].y; i++) {
        temp.at<uint8_t>(bounds[2].x, i) = 100;
    }
    for (int i = bounds[1].x; i <= bounds[3].x; i++) {
        temp.at<uint8_t>(i, bounds[3].y) = 100;
    }

    return temp;

}

// Calcule le Centre de Gravite
cv::Point ImageAnalysis::GravityCenter(int GrayLevel) {

    int x = 0;
    int y = 0;

    //pour calculer le nombre totale du de la boite englobante
    int counterGlob = 0;
    //calculer le nombre de pixel de chaque ligne et colonne
    int counter = 0;

    //recuperer la boite englobante
    cv::Point *bounds = findBounds(GrayLevel);

    //calculer le X de Gravity Center
    for (int i = bounds[0].x ; i <= bounds[3].x; i++) {

        counter = 0;
        for (int j = bounds[0].y ; j <= bounds[3].y; j++) {

            if (image.at<uint8_t>(i, j) >= 200) {
                counterGlob++;
                counter++;
            }

        }
        x += counter * i;

    }

    //Calculer le Y de Gravity Center
    for (int i = bounds[0].y; i <= bounds[3].y; i++) {

        counter = 0;
        for (int j = bounds[0].x; j <= bounds[3].x; j++) {

            if (image.at<uint8_t>(j, i) >= 200){
                counter++;
            }

        }
        y += counter * i;

    }

    return cv::Point(x/counterGlob , y/counterGlob);

}



// Decaler les Pixels Blancs Dans Une Direction
cv::Mat ImageAnalysis::Shift (cv::Point *Bounds, int Direction, int Position) {

    cv::Mat temp = image.clone();
    cv::threshold(temp, temp, 0, 0, cv::THRESH_BINARY);

    switch (Direction) {

    case 0: // UP

        for (int i = Bounds[0].x ; i <= Bounds[3].x; i++) {

            for (int j = Bounds[0].y ; j <= Bounds[3].y; j++) {

                if(i - Position < 0)
                    return image;


                temp.at<uint8_t>(i - Position, j) = image.at<uint8_t>(i, j);

            }

        }

        break;

    case 1: // DOWN

        for (int i = Bounds[0].x ; i <= Bounds[3].x; i++) {

            for (int j = Bounds[0].y ; j <= Bounds[3].y; j++) {

                if(i + Position > temp.rows - 1)
                    return image;


                temp.at<uint8_t>(i + Position, j) = image.at<uint8_t>(i, j);

            }

        }

        break;

    case 2: // Left

        for (int i = Bounds[0].x ; i <= Bounds[3].x; i++) {

            for (int j = Bounds[0].y ; j <= Bounds[3].y; j++) {

                if(j - Position < 0)
                    return image;

                temp.at<uint8_t>(i, j - Position) = image.at<uint8_t>(i, j);

            }

        }

        break;

    case 3: // Right

        for (int i = Bounds[0].x ; i <= Bounds[3].x; i++) {

            for (int j = Bounds[0].y ; j <= Bounds[3].y; j++) {

                if(j + Position > temp.cols - 1)
                    return image;


                temp.at<uint8_t>(i, j + Position) = image.at<uint8_t>(i, j);

            }

        }

        break;

    }

    return temp;

}


//Miroire d'image
cv::Mat ImageAnalysis::FlipImage() {

    cv::Mat temp = image.clone();
    cv::threshold(temp, temp, 0, 0, cv::THRESH_BINARY);

    for (int i = 0; i < image.rows; i++) {

        for (int j = 0; j < image.cols; j++) {

            temp.at<uint8_t>(i, image.cols - 1 - j) = image.at<uint8_t>(i, j);

        }

    }

    return temp;

}

//sauvgarder une image
void ImageAnalysis::saveImage(std::string path){
    cv::imwrite(path,this->image);
}


/*********************************TCHIEBYCHEV SECTION************************************************/
//p(n,N)  n = p ou q , N = image ROWS
double ImageAnalysis::Calculate1(double n, double N) {

    double sum = N;
    for (int i = 1; i <= n; i++) {

        sum *= ((1 - (pow(i,2)/pow(N,2))));

    }

    sum /= (2 * n + 1);

    return sum;

}

//x image pixel itensity
double ImageAnalysis::Calculate2(double n, double N , double x) {

    if (n == 0) {
        return 1.0;
    }
    else if (n == 1) {
        return (2 * x + 1 - N) / N;
    }
    else {
        return (((2 * n - 1)*Calculate2(1,N,x)*Calculate2(n-1,N,x)) - ((n-1)*(1-(pow(n-1,2)/pow(N,2)))*Calculate2(n-2 ,N,x)))/n ;
    }

}

//tchebychev
double ImageAnalysis::TMoment(double p , double q) {

    double T = 0;

    for (int y = 0; y < image.cols; y++) {

        for (int x = 0; x < image.rows; x++) {

            if (image.at<uint8_t>(x, y) != 0) {

                T += Calculate2(p, image.cols, x)*Calculate2(q, image.cols, y)*image.at<uint8_t>(x, y);

            }


        }

    }

    T /= (Calculate1(p, image.cols) * Calculate1(q, image.cols));

    return T;
}


//Vector moment
std::vector<double> ImageAnalysis::MomentVector(int order, bool isMethod1, bool isNormalized) {

    int VectorLenght = 0;

    for(int i = 1 ; i <= order+1 ; i++){
        VectorLenght += i;
    }

    std::vector<double> V;

    int p = 0;
    int q = 0;

    double norm = 0;

    int Methode1Length = 0;

    for (int i = 0; i < VectorLenght; i++) {

        if(!isMethod1){

            V.push_back(TMoment(p, q));
            norm += pow(V[i], 2);
            if (p + q == order) {
                p++;
                q = 0;
            }
            else {
                q++;
            }

        }else{

            if (p + q == order) {

                double M = TMoment(p, q);

                V.push_back(M);
                p++;
                q = 0;
                Methode1Length++;

                norm += pow(M, 2);

            }
            else {
                q++;
            }

        }


    }

    std::vector<double> newVec;

    if(isNormalized){

        double min = V[0];
        double max = V[0];

        for(double value : V){

            if(min > value){
                min = value;
            }

            if(max < value){
                max = value;
            }

        }

        for(double value : V){

            //newVec.push_back(value / sqrt(norm));
            newVec.push_back((value-min) / (max-min));

        }

    }else{

        newVec = V;

    }

    return newVec;

}





//shift image on center
cv::Mat ImageAnalysis::shiftedToPoint(cv::Point *bounds, cv::Point ptFixe, cv::Point massCenter) {

    cv::Mat temp = image.clone();

    //Distance between massCenter and fixedPoint to Add
    if (massCenter.y - ptFixe.y > 0) {
        temp = Shift(bounds, 2, (massCenter.y - ptFixe.y)).clone();
    }
    else {
        temp = Shift(bounds, 3, (ptFixe.y - massCenter.y)).clone();

    }

    bounds = ImageAnalysis(temp).findBounds(1);

    if (massCenter.x - ptFixe.x > 0) {
        temp = ImageAnalysis(temp).Shift(bounds, 0, (massCenter.x - ptFixe.x)).clone();

    }
    else {
        temp = ImageAnalysis(temp).Shift(bounds, 1, (ptFixe.x - massCenter.x)).clone();

    }

    return temp;

}
