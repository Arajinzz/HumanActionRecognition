#ifndef RECOGNIZE_H
#define RECOGNIZE_H

#include <QString>
#include "opencv2/opencv.hpp"
#include <QDir>
#include <QFile>
#include "classifier.h"
#include <QMessageBox>
#include "settings.h"


struct Params {
    std::vector<double> V;
    int i;
};

typedef Params Params;

class Recognize : QObject
{
public:
    Recognize(QString fileName);

    bool addInfo(int choice,QString name, std::vector<double> infos,bool forceAppend);
    bool AppendInFile(QString filename, QString name, std::vector<double> infos,bool forceAppend);
    int CheckIfExist(QString filename, std::vector<double> infos);
    bool Supprimer(QString filename, QString name);
    bool Checkbyname(QString filename, QString name);
    bool checkCheck(int **choices , Classifier cls,bool isMoving, QString Name);

    Params* ChoosingNEW(int **choices , Classifier cls,bool isMoving);
    QString FinalChoosingNEW(int **choices , Classifier cls, bool isPoweredUP, bool isMoving);

    Params* Choosing(int **choices , Classifier cls,bool isMoving);

    QString FinalChoosing(int **choices , Classifier cls, bool isPoweredUP, bool isMoving);
    QString PowerUp(Params *params, bool isMoving);

    QString fileName;
    QString PreClassification;


private:



};

#endif // RECOGNIZE_H
