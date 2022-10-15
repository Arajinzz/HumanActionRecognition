#include "addmouvv2.h"

AddMouvV2::AddMouvV2(int Order , Recognize *rec, bool isMth1)
{

    this->Order = Order;
    this->rec = rec;
    this->isMth1 = isMth1;

    this->vectorLength = ((Order+1)*(Order+2))/2;

}


//Ajouter Un Mouvement a Une Base
//int Choice c'est L'indice qui indique le nom du Mouvement
bool AddMouvV2::Add(std::vector<double> featuresMEI,std::vector<double> featuresMHI, QString name,int choice, bool isMethod1,bool isNormalized){

    double normMEI = 0;
    double normMHI = 0;

    //Si on a choisie un Video
    if(!featuresMEI.empty() && !featuresMHI.empty()){

        std::vector<double> tempFeaturesMEI;
        std::vector<double> tempFeaturesMHI;

        for(int i = 0 ; i < vectorLength ; i++){

            tempFeaturesMEI.push_back(featuresMEI[i]);
            tempFeaturesMHI.push_back(featuresMHI[i]);

            normMEI += pow(tempFeaturesMEI[i],2);
            normMHI += pow(tempFeaturesMHI[i],2);

        }

        if(isMethod1){

            int p = 0;
            int q = 0;

            normMEI = 0;
            normMHI = 0;

            int newLength = 0;

            std::vector<double> tempFeaturesMEI_2;
            std::vector<double> tempFeaturesMHI_2;

            for(int i = 0 ; i < vectorLength ; i++){

                if (p + q == Order) {

                    tempFeaturesMEI_2.push_back(tempFeaturesMEI[i]);
                    tempFeaturesMHI_2.push_back(tempFeaturesMHI[i]);

                    normMEI += pow(tempFeaturesMEI[i],2);
                    normMHI += pow(tempFeaturesMHI[i],2);

                    newLength++;

                    p++;

                    q = 0;

                }
                else {

                    q++;

                }

            }

            tempFeaturesMEI.clear();
            tempFeaturesMHI.clear();

            for(int i = 0 ; i < tempFeaturesMEI_2.size() ; i++){

                tempFeaturesMEI.push_back(tempFeaturesMEI_2[i]);
                tempFeaturesMHI.push_back(tempFeaturesMHI_2[i]);

            }

            vectorLength = newLength;

        }

        if(isNormalized){

            double minMEI = tempFeaturesMEI[0];
            double minMHI = tempFeaturesMHI[0];

            double maxMEI = tempFeaturesMEI[0];
            double maxMHI = tempFeaturesMHI[0];

            for(int i = 1 ; i < vectorLength ; i++){

                if(minMEI > tempFeaturesMEI[i]){
                    minMEI = tempFeaturesMEI[i];
                }

                if(minMHI > tempFeaturesMHI[i]){
                    minMHI = tempFeaturesMHI[i];
                }

                if(maxMEI < tempFeaturesMEI[i]){
                    maxMEI = tempFeaturesMEI[i];
                }

                if(maxMHI < tempFeaturesMHI[i]){
                    maxMHI = tempFeaturesMHI[i];
                }

            }

            for(int i = 0 ; i < vectorLength ; i++){

                //tempFeaturesMEI[i] /= sqrt(normMEI);
                //tempFeaturesMHI[i] /= sqrt(normMHI);

                tempFeaturesMEI[i] = (tempFeaturesMEI[i]-minMEI)/(maxMEI-minMEI);
                tempFeaturesMHI[i] = (tempFeaturesMHI[i]-minMHI)/(maxMHI-minMHI);

            }
        }


        //Inserer Les Moment dans un Fichier
        bool b = rec->addInfo(choice,name,tempFeaturesMEI,false);
        //Si le moment de MEI et bien inserer on insere le Deusieme Moment
        if(b)
           return rec->addInfo(choice,name,tempFeaturesMHI,true);

    }

    return false;

}


//Des Button Pour Chaque Mouvement

bool AddMouvV2::Walk(std::vector<double> featuresMEI,std::vector<double> featuresMHI,QString name,bool isNormalized)
{
    return this->Add(featuresMEI,featuresMHI,name,4,isMth1,isNormalized);
}

bool AddMouvV2::Jump(std::vector<double> featuresMEI,std::vector<double> featuresMHI,QString name,bool isNormalized)
{
    return this->Add(featuresMEI,featuresMHI,name,0,isMth1,isNormalized);
}

bool AddMouvV2::Run(std::vector<double> featuresMEI,std::vector<double> featuresMHI,QString name,bool isNormalized)
{
    return this->Add(featuresMEI,featuresMHI,name,1,isMth1,isNormalized);
}

bool AddMouvV2::Side(std::vector<double> featuresMEI,std::vector<double> featuresMHI,QString name,bool isNormalized)
{
    return this->Add(featuresMEI,featuresMHI,name,2,isMth1,isNormalized);
}

bool AddMouvV2::Skip(std::vector<double> featuresMEI,std::vector<double> featuresMHI,QString name,bool isNormalized)
{
    return this->Add(featuresMEI,featuresMHI,name,3,isMth1,isNormalized);
}

bool AddMouvV2::Bend(std::vector<double> featuresMEI,std::vector<double> featuresMHI,QString name,bool isNormalized)
{
    return this->Add(featuresMEI,featuresMHI,name,5,isMth1,isNormalized);
}

bool AddMouvV2::Jack(std::vector<double> featuresMEI,std::vector<double> featuresMHI,QString name,bool isNormalized)
{
    return this->Add(featuresMEI,featuresMHI,name,6,isMth1,isNormalized);
}

bool AddMouvV2::Pjump(std::vector<double> featuresMEI,std::vector<double> featuresMHI,QString name,bool isNormalized)
{
    return this->Add(featuresMEI,featuresMHI,name,7,isMth1,isNormalized);
}

bool AddMouvV2::Wave1(std::vector<double> featuresMEI,std::vector<double> featuresMHI,QString name,bool isNormalized)
{
    return this->Add(featuresMEI,featuresMHI,name,8,isMth1,isNormalized);
}

bool AddMouvV2::Wave2(std::vector<double> featuresMEI,std::vector<double> featuresMHI,QString name,bool isNormalized)
{
    return this->Add(featuresMEI,featuresMHI,name,9,isMth1,isNormalized);
}
