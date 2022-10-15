#ifndef CLASSIFIER_H
#define CLASSIFIER_H

/*
 * Class Utilisee pour recuperer les Donnees depuis une Base (Profile)
 * et Recuperer des Donnes Pour Classifier Un Mouvement
 * */


#include <QString>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include "opencv2/opencv.hpp"
#include "mouvementclass.h"

class Classifier
{
public:
    Classifier();
    Classifier(QString filename);
    Classifier(QString filename ,std::vector<double> MEItest, std::vector<double> MHItest);

    void GetAllFeatures();
    void GetAllFeaturesWithoutDistances();
    void Liberer();
    void ManualInPlace(mouvementClass *_bend, mouvementClass *_jack, mouvementClass *_pjump, mouvementClass *_wave1, mouvementClass *_wave2);
    void ManualNoPlace(mouvementClass *_walk, mouvementClass *_run, mouvementClass *_jump, mouvementClass *_skip, mouvementClass *_side);

    double determineMin(std::vector<double> v);

    int nearestN(std::vector<double> V11, std::vector<double> V22);
    int determineMinIndex(std::vector<double> V, double min);

    int **MatrixNoPlace_MEI();
    int **MatrixInPlace_MEI();
    int **MatrixInPlace_MHI();
    int **MatrixNoPlace_MHI();

    //Features
    mouvementClass *Walk;
    mouvementClass *Run;
    mouvementClass *Skip;
    mouvementClass *Side;
    mouvementClass *Jump;

    mouvementClass *Bend;
    mouvementClass *Wave1;
    mouvementClass *Wave2;
    mouvementClass *Jack;
    mouvementClass *Pjump;

private:

    //Test
    std::vector<double> MEItest;
    std::vector<double> MHItest;

    //Le nom du profile Utilisee (La Base Utilisee)
    QString filename;
};

#endif // CLASSIFIER_H
