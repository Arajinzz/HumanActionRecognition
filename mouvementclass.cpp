#include "mouvementclass.h"

/*
 * Class qui Va Contient des Informations Sur La video
 * Comme les Moment du Tchiebchev
 * et Les Distance entre 2 Video
 * */


//Ce Constructeur Utilisee pour recuperer les Moment de Tchebiechev sans calcule des Distance
mouvementClass::mouvementClass(QString filename){

    this->filename = filename;
    GetFeatures();

}


//Ce Constructeur Utilisee pour recuperer les Moment de Tchebiechev ainsi le calcule des Distance
mouvementClass::mouvementClass(QString filename,std::vector<double> MEItest,std::vector<double> MHItest)
{
    this->filename = filename;
    this->MEItest = MEItest;
    this->MHItest = MHItest;
    GetFeatures();
    CalculateDistance();
}


mouvementClass::mouvementClass(std::vector<std::vector<double>> MEI, std::vector<std::vector<double>> MHI,std::vector<double> MEItest,std::vector<double> MHItest){

    for(int i = 0 ; i < MEI.size() ; i++){

        this->mouvementMEI.push_back(MEI[i]);
        this->mouvementMEI.push_back(MHI[i]);

    }

    this->MEItest = MEItest;
    this->MHItest = MHItest;

    CalculateDistance();

}


// Recuperer les Moment de Tchiebychev de La Base (Profile)
void mouvementClass::GetFeatures(){

    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    bool isMEI = true;
    bool bypassFirst = true;

    while(!in.atEnd()){

        bypassFirst = true;

        QString line = in.readLine();
        QStringList list = line.split(":");


        std::vector<double> temp;
        foreach (QString str, list) {

            if(bypassFirst){
                bypassFirst = false;
                continue;
            }

            temp.push_back(str.toDouble());
        }

        if(isMEI){
            mouvementMEI.push_back(temp);
            isMEI = false;
        }
        else{
            mouvementMHI.push_back(temp);
            isMEI = true;
        }

    }

    file.close();

}


// Calculer les Distances Euclidean
void mouvementClass::CalculateDistance() {

    double distance;
    std::vector<double> Distances;

    for(std::vector<double> M1 : mouvementMEI){

        distance = 0;

        for (int i = 0; i < M1.size(); i++) {
            distance += pow((M1[i] - MEItest[i]), 2);
        }

        distanceMEI.push_back(sqrt(distance));
    }

    for(std::vector<double> M1 : mouvementMHI){

        distance = 0;

        for (int i = 0; i < M1.size(); i++) {
            distance += pow((M1[i] - MHItest[i]), 2);
        }

        distanceMHI.push_back(sqrt(distance));
    }

}


void mouvementClass::ForBypass(int index){

    distanceMEI.clear();
    distanceMHI.clear();

    mouvementMEI.erase(mouvementMEI.begin() + index);
    mouvementMHI.erase(mouvementMHI.begin() + index);

    CalculateDistance();

}
