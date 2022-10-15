#ifndef CROSSVALIDATION_H
#define CROSSVALIDATION_H

/*
 * Class Pour Calculer le Taux de Reconnaissance
 * Du Modele
 * */

#include "classifier.h"
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <recognize.h>
#include "settings.h"

class CrossValidation
{
public:
    CrossValidation(QString fileNameInPlace, QString fileNameNoPlace,Settings *setInplace, Settings *setNoplace);

    double PerformeAllTest();
    double PerformTest(std::vector<std::vector<double>> toTestMEI, std::vector<std::vector<double>> toTestMHI, QString MvtName , bool isMoving, int choice,QString fileName);

    double PerformeNoPlaceTest();
    double PerformePlaceTest();

    std::vector<std::vector<double>> ByPass(std::vector<std::vector<double>> V, int j);

    void TauxPreClassMEI();
    double PerformeAllTestNEW();
    double PerformNewTest(std::vector<std::vector<double>> toTestMEI, std::vector<std::vector<double>> toTestMHI, QString MvtName , bool isMoving , int choice,QString fileName);
    double PerformTestNNN(std::vector<std::vector<double>> toTestMEI, std::vector<std::vector<double>> toTestMHI, QString MvtName , bool isMoving , int choice,QString fileName);

    double Taux1;
    double Taux2;

    double preTaux1;
    double preTaux2;

private:
    Classifier *clsInplace;
    Classifier *clsNoplace;

    QString fileNameInPlace;
    QString fileNameNoPlace;

    Settings *setInplace;
    Settings *setNoplace;

};

#endif // CROSSVALIDATION_H
