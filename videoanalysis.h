#ifndef VIDEOANALYSIS_H
#define VIDEOANALYSIS_H

/*
 * Class Pour des Differentes Manipulations dans un Video
 *
 * */

#include <opencv2/opencv.hpp>
#include "imageanalysis.h"
#include <QDebug>

using namespace std;

class VideoAnalysis
{
public:
    VideoAnalysis();
    VideoAnalysis(string path_video);

    void LoadVideo();
    void StoreVideo(vector<cv::Mat> frames, string savePath);

    cv::Mat GenerateMEI(int frameEnd);
    cv::Mat GenerateMHI(int frameEnd, int tau, int variation);
    cv::Mat NoiseElim(cv::Mat frame);
    cv::Mat ShiftUpLeft(cv::Mat frame, cv::Point *bounds);
    cv::Mat centredMHI(int tau, int variation, int frames);
    cv::Mat centredMEI(int frames);

    bool isMoving(bool CheckingDirection);

    cv::Mat Original;

    vector<cv::Mat> MEI_V;
    vector<cv::Mat> MHI_V;

private:
    vector<cv::Mat> Allframes;
    string path_video;


};

#endif // VIDEOANALYSIS_H
