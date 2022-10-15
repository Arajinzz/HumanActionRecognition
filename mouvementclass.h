#ifndef MOUVEMENTCLASS_H
#define MOUVEMENTCLASS_H

/*
 * Class qui Va Contient des Informations Sur La video
 * Comme les Moment du Tchiebchev
 * et Les Distance entre 2 Video
 * */

#include "opencv2/opencv.hpp"
#include <QString>
#include <QFile>
#include <QTextStream>

class mouvementClass
{
public:
    mouvementClass(QString filename);
    mouvementClass(QString filename, std::vector<double> MEItest, std::vector<double> MHItest);
    mouvementClass(std::vector<std::vector<double>> MEI, std::vector<std::vector<double>> MHI,std::vector<double> MEItest,std::vector<double> MHItest);
    void GetFeatures();
    void CalculateDistance();
    void ForBypass(int index);

    //features
    std::vector<std::vector<double>> mouvementMEI;
    std::vector<std::vector<double>> mouvementMHI;

    //distances
    std::vector<double> distanceMEI;
    std::vector<double> distanceMHI;

private:
    std::vector<double> MEItest;
    std::vector<double> MHItest;
    QString filename;

};

#endif // MOUVEMENTCLASS_H
