#ifndef IMAGEANALYSIS_H
#define IMAGEANALYSIS_H

/*
 * Class Avec des Different Operation
 * Sur Les Images
 * */

#include <opencv2/opencv.hpp>

class ImageAnalysis
{
public:
    ImageAnalysis(cv::Mat image);

    cv::Point GravityCenter(int GrayLevel);
    cv::Point* findBounds(int grayLevel);

    cv::Mat drawRectangle(cv::Point *bounds);
    cv::Mat Shift (cv::Point *Bounds, int Direction, int Position);
    cv::Mat FlipImage();
    cv::Mat shiftedToPoint(cv::Point *bounds, cv::Point ptFixe, cv::Point massCenter);

    void saveImage(std::string path);

    double Calculate1(double n, double N);
    double Calculate2(double n, double N , double x);
    double TMoment(double p , double q);

    std::vector<double> MomentVector(int order, bool isMethod1, bool isNormalized);

private:
    cv::Mat image;
};

#endif // IMAGEANALYSIS_H
