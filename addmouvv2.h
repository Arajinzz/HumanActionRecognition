#ifndef ADDMOUVV2_H
#define ADDMOUVV2_H

#include "recognize.h"
#include "imageanalysis.h"
#include "videoanalysis.h"
#include "opencv2/opencv.hpp"
#include "settings.h"

class AddMouvV2
{
public:
    AddMouvV2(int Order , Recognize *rec, bool isMth1);

    bool Add(std::vector<double> featuresMEI,std::vector<double> featuresMHI,QString name, int choice, bool isMethod1,bool isNormalized);

    bool Walk(std::vector<double> featuresMEI,std::vector<double> featuresMHI,QString name,bool isNormalized);
    bool Run(std::vector<double> featuresMEI,std::vector<double> featuresMHI,QString name,bool isNormalized);
    bool Jump(std::vector<double> featuresMEI,std::vector<double> featuresMHI,QString name,bool isNormalized);
    bool Side(std::vector<double> featuresMEI,std::vector<double> featuresMHI,QString name,bool isNormalized);
    bool Skip(std::vector<double> featuresMEI,std::vector<double> featuresMHI,QString name,bool isNormalized);
    bool Bend(std::vector<double> featuresMEI,std::vector<double> featuresMHI,QString name,bool isNormalized);
    bool Jack(std::vector<double> featuresMEI,std::vector<double> featuresMHI,QString name,bool isNormalized);
    bool Wave1(std::vector<double> featuresMEI,std::vector<double> featuresMHI,QString name,bool isNormalized);
    bool Wave2(std::vector<double> featuresMEI,std::vector<double> featuresMHI,QString name,bool isNormalized);
    bool Pjump(std::vector<double> featuresMEI,std::vector<double> featuresMHI,QString name,bool isNormalized);

private:
    Recognize *rec;
    bool isMth1;

    int vectorLength;
    int Order;

};

#endif // ADDMOUVV2_H
