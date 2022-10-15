#include "classifier.h"

/*
 * Class Utilisee pour recuperer les Donnees depuis une Base (Profile)
 * et Recuperer des Donnes Pour Classifier Un Mouvement
 * */

Classifier::Classifier(){

}

Classifier::Classifier(QString filename){
    this->filename = filename;
}

Classifier::Classifier(QString filename ,std::vector<double> MEItest, std::vector<double> MHItest)
{
    this->MEItest = MEItest;
    this->MHItest = MHItest;
    this->filename = filename;
}

//Recuperer tout les Donnees du la Base ou le profile (filename)
//Sans Distances pour les utilisee dans la CrossValidation
void Classifier::GetAllFeaturesWithoutDistances(){

    Walk = new mouvementClass(filename+"/NOPLACE/Walk");
    Run = new mouvementClass(filename+"/NOPLACE/Run");
    Side = new mouvementClass(filename+"/NOPLACE/Side");
    Skip = new mouvementClass(filename+"/NOPLACE/Skip");
    Jump = new mouvementClass(filename+"/NOPLACE/Jump");

    Pjump = new mouvementClass(filename+"/INPLACE/Pjump");
    Wave2 = new mouvementClass(filename+"/INPLACE/Wave2");
    Wave1 = new mouvementClass(filename+"/INPLACE/Wave1");
    Jack = new mouvementClass(filename+"/INPLACE/Jack");
    Bend = new mouvementClass(filename+"/INPLACE/Bend");

}

//Recuperer tout les Donnees du la Base ou le profile (filename)
//Avec les Distances
void Classifier::GetAllFeatures(){

    Walk = new mouvementClass(filename+"/NOPLACE/Walk", MEItest , MHItest);
    Run = new mouvementClass(filename+"/NOPLACE/Run", MEItest , MHItest);
    Side = new mouvementClass(filename+"/NOPLACE/Side", MEItest , MHItest);
    Skip = new mouvementClass(filename+"/NOPLACE/Skip", MEItest , MHItest);
    Jump = new mouvementClass(filename+"/NOPLACE/Jump", MEItest , MHItest);

    Pjump = new mouvementClass(filename+"/INPLACE/Pjump", MEItest , MHItest);
    Wave2 = new mouvementClass(filename+"/INPLACE/Wave2", MEItest , MHItest);
    Wave1 = new mouvementClass(filename+"/INPLACE/Wave1", MEItest , MHItest);
    Jack = new mouvementClass(filename+"/INPLACE/Jack", MEItest , MHItest);
    Bend = new mouvementClass(filename+"/INPLACE/Bend", MEItest , MHItest);


}


//Pour determine l'index d'une valeur dans un Vecteur
int Classifier::determineMinIndex(std::vector<double> V, double min) {

    for (int i = 0; i < V.size(); i++) {

        if (V[i] == min)
            return i;

    }

}


//Pour determiner la valeur Minimale dans un Vecteur
double Classifier::determineMin(std::vector<double> v) {

    double min = v[0];
    for (int i = 1; i < v.size(); i++) {
        if (v[i] < min)
            min = v[i];
    }

    return min;

}


//NEAREST NIGHBORGHS Choisir les Meilleur Distances
//Pour Classifiers La Video
int Classifier::nearestN(std::vector<double> V11, std::vector<double> V22) {

    std::vector<double> V1;
    std::vector<double> V2;

    //Copier les Vecteurs
    if (!V11.empty() && !V22.empty()) {
        for (int i = 0; i < V11.size(); i++) {
            V1.push_back(V11[i]);
        }

        for (int i = 0; i < V22.size(); i++) {
            V2.push_back(V22[i]);
        }
    }

    double min1 = 0;
    double min2 = 0;

    int k1 = 0;
    int k2 = 0;

    for (int i = 0; i < 5; i++) {

        //Determiner le Plus Proche Vecteur
        //Le Vecteur de Distance qui est Plus Proche
        if (!V1.empty() && !V2.empty()) {

            min1 = determineMin(V1);
            min2 = determineMin(V2);

            // Effacer le Minimum pour recomparer
            if (min1 < min2) {
                k1++;
                V1.erase(V1.begin() + determineMinIndex(V1, min1));
            }
            else {
                k2++;
                V2.erase(V2.begin() + determineMinIndex(V2, min2));
            }

        }

        if (k1 == 3 || k2 == 3)
            break;



    }

    if (k1 > k2) {
        return 1;
    }
    else {
        return 0;
    }

}


//Pour Comparer Les Distances des MEI et MHI de Tout Les Mouvement
int** Classifier::MatrixNoPlace_MEI() {

    int **choices = new int*[5];

    for(int i = 0 ; i < 5 ; i++){
        choices[i] = new int[5];
    }

    //walk column
    choices[0][0] = nearestN(Walk->distanceMEI, Run->distanceMEI);
    choices[1][0] = nearestN(Walk->distanceMEI, Jump->distanceMEI);
    choices[2][0] = nearestN(Walk->distanceMEI, Skip->distanceMEI);
    choices[3][0] = nearestN(Walk->distanceMEI, Side->distanceMEI);
    choices[4][0] = 1;

    //run
    choices[0][1] = nearestN(Run->distanceMEI, Walk->distanceMEI);
    choices[1][1] = nearestN(Run->distanceMEI, Jump->distanceMEI);
    choices[2][1] = nearestN(Run->distanceMEI, Skip->distanceMEI);
    choices[3][1] = nearestN(Run->distanceMEI, Side->distanceMEI);
    choices[4][1] = 1;

    //jump
    choices[0][2] = nearestN(Jump->distanceMEI, Run->distanceMEI);
    choices[1][2] = nearestN(Jump->distanceMEI, Walk->distanceMEI);
    choices[2][2] = nearestN(Jump->distanceMEI, Skip->distanceMEI);
    choices[3][2] = nearestN(Jump->distanceMEI, Side->distanceMEI);
    choices[4][2] = 1;


    //skip
    choices[0][3] = nearestN(Skip->distanceMEI, Run->distanceMEI);
    choices[1][3] = nearestN(Skip->distanceMEI, Walk->distanceMEI);
    choices[2][3] = nearestN(Skip->distanceMEI, Jump->distanceMEI);
    choices[3][3] = nearestN(Skip->distanceMEI, Side->distanceMEI);
    choices[4][3] = 1;

    //side
    choices[0][4] = nearestN(Side->distanceMEI, Run->distanceMEI);
    choices[1][4] = nearestN(Side->distanceMEI, Walk->distanceMEI);
    choices[2][4] = nearestN(Side->distanceMEI, Jump->distanceMEI);
    choices[3][4] = nearestN(Side->distanceMEI, Skip->distanceMEI);
    choices[4][4] = 1;

    return choices;


}


int** Classifier::MatrixInPlace_MEI() {

    int **choices = new int*[5];

    for(int i = 0 ; i < 5 ; i++){
        choices[i] = new int[5];
    }

    //Bend column
    choices[0][0] = nearestN(Bend->distanceMEI, Jack->distanceMEI);
    choices[1][0] = nearestN(Bend->distanceMEI, Wave1->distanceMEI);
    choices[2][0] = nearestN(Bend->distanceMEI, Wave2->distanceMEI);
    choices[3][0] = nearestN(Bend->distanceMEI, Pjump->distanceMEI);
    choices[4][0] = 1;



    //Jack
    choices[0][1] = nearestN(Jack->distanceMEI, Bend->distanceMEI);
    choices[1][1] = nearestN(Jack->distanceMEI, Pjump->distanceMEI);
    choices[2][1] = nearestN(Jack->distanceMEI, Wave1->distanceMEI);
    choices[3][1] = nearestN(Jack->distanceMEI, Wave2->distanceMEI);
    choices[4][1] = 1;

    //Pjump
    choices[0][2] = nearestN(Pjump->distanceMEI, Bend->distanceMEI);
    choices[1][2] = nearestN(Pjump->distanceMEI, Jack->distanceMEI);
    choices[2][2] = nearestN(Pjump->distanceMEI, Wave1->distanceMEI);
    choices[3][2] = nearestN(Pjump->distanceMEI, Wave2->distanceMEI);
    choices[4][2] = 1;


    //Wave1
    choices[0][3] = nearestN(Wave1->distanceMEI, Bend->distanceMEI);
    choices[1][3] = nearestN(Wave1->distanceMEI, Jack->distanceMEI);
    choices[2][3] = nearestN(Wave1->distanceMEI, Pjump->distanceMEI);
    choices[3][3] = nearestN(Wave1->distanceMEI, Wave2->distanceMEI);
    choices[4][3] = 1;

    //Wave2
    choices[0][4] = nearestN(Wave2->distanceMEI, Bend->distanceMEI);
    choices[1][4] = nearestN(Wave2->distanceMEI, Pjump->distanceMEI);
    choices[2][4] = nearestN(Wave2->distanceMEI, Jack->distanceMEI);
    choices[3][4] = nearestN(Wave2->distanceMEI, Wave1->distanceMEI);
    choices[4][4] = 1;

    return choices;

}



int** Classifier::MatrixNoPlace_MHI() {

    int **choices = new int*[5];

    for(int i = 0 ; i < 5 ; i++){
        choices[i] = new int[5];
    }

    //walk column
    choices[0][0] = nearestN(Walk->distanceMHI, Run->distanceMHI);
    choices[1][0] = nearestN(Walk->distanceMHI, Jump->distanceMHI);
    choices[2][0] = nearestN(Walk->distanceMHI, Skip->distanceMHI);
    choices[3][0] = nearestN(Walk->distanceMHI, Side->distanceMHI);
    choices[4][0] = 1;

    //run
    choices[0][1] = nearestN(Run->distanceMHI, Walk->distanceMHI);
    choices[1][1] = nearestN(Run->distanceMHI, Jump->distanceMHI);
    choices[2][1] = nearestN(Run->distanceMHI, Skip->distanceMHI);
    choices[3][1] = nearestN(Run->distanceMHI, Side->distanceMHI);
    choices[4][1] = 1;

    //jump
    choices[0][2] = nearestN(Jump->distanceMHI, Run->distanceMHI);
    choices[1][2] = nearestN(Jump->distanceMHI, Walk->distanceMHI);
    choices[2][2] = nearestN(Jump->distanceMHI, Skip->distanceMHI);
    choices[3][2] = nearestN(Jump->distanceMHI, Side->distanceMHI);
    choices[4][2] = 1;


    //skip
    choices[0][3] = nearestN(Skip->distanceMHI, Run->distanceMHI);
    choices[1][3] = nearestN(Skip->distanceMHI, Walk->distanceMHI);
    choices[2][3] = nearestN(Skip->distanceMHI, Jump->distanceMHI);
    choices[3][3] = nearestN(Skip->distanceMHI, Side->distanceMHI);
    choices[4][3] = 1;

    //side
    choices[0][4] = nearestN(Side->distanceMHI, Run->distanceMHI);
    choices[1][4] = nearestN(Side->distanceMHI, Walk->distanceMHI);
    choices[2][4] = nearestN(Side->distanceMHI, Jump->distanceMHI);
    choices[3][4] = nearestN(Side->distanceMHI, Skip->distanceMHI);
    choices[4][4] = 1;

    return choices;


}


int** Classifier::MatrixInPlace_MHI() {

    int **choices = new int*[5];

    for(int i = 0 ; i < 5 ; i++){
        choices[i] = new int[5];
    }

    //Bend column
    choices[0][0] = nearestN(Bend->distanceMHI, Jack->distanceMHI);
    choices[1][0] = nearestN(Bend->distanceMHI, Wave1->distanceMHI);
    choices[2][0] = nearestN(Bend->distanceMHI, Wave2->distanceMHI);
    choices[3][0] = nearestN(Bend->distanceMHI, Pjump->distanceMHI);
    choices[4][0] = 1;

    //Jack
    choices[0][1] = nearestN(Jack->distanceMHI, Bend->distanceMHI);
    choices[1][1] = nearestN(Jack->distanceMHI, Pjump->distanceMHI);
    choices[2][1] = nearestN(Jack->distanceMHI, Wave1->distanceMHI);
    choices[3][1] = nearestN(Jack->distanceMHI, Wave2->distanceMHI);
    choices[4][1] = 1;

    //Pjump
    choices[0][2] = nearestN(Pjump->distanceMHI, Bend->distanceMHI);
    choices[1][2] = nearestN(Pjump->distanceMHI, Jack->distanceMHI);
    choices[2][2] = nearestN(Pjump->distanceMHI, Wave1->distanceMHI);
    choices[3][2] = nearestN(Pjump->distanceMHI, Wave2->distanceMHI);
    choices[4][2] = 1;


    //Wave1
    choices[0][3] = nearestN(Wave1->distanceMHI, Bend->distanceMHI);
    choices[1][3] = nearestN(Wave1->distanceMHI, Jack->distanceMHI);
    choices[2][3] = nearestN(Wave1->distanceMHI, Pjump->distanceMHI);
    choices[3][3] = nearestN(Wave1->distanceMHI, Wave2->distanceMHI);
    choices[4][3] = 1;

    //Wave2
    choices[0][4] = nearestN(Wave2->distanceMHI, Bend->distanceMHI);
    choices[1][4] = nearestN(Wave2->distanceMHI, Pjump->distanceMHI);
    choices[2][4] = nearestN(Wave2->distanceMHI, Jack->distanceMHI);
    choices[3][4] = nearestN(Wave2->distanceMHI, Wave1->distanceMHI);
    choices[4][4] = 1;

    return choices;

}


void Classifier::ManualInPlace(mouvementClass *_bend, mouvementClass *_jack, mouvementClass *_pjump, mouvementClass *_wave1, mouvementClass *_wave2){

    this->Bend = _bend;
    this->Jack = _jack;
    this->Pjump = _pjump;
    this->Wave1 = _wave1;
    this->Wave2 = _wave2;

}

void Classifier::ManualNoPlace(mouvementClass *_walk, mouvementClass *_run, mouvementClass *_jump, mouvementClass *_skip, mouvementClass *_side){

    this->Walk = _walk;
    this->Run = _run;
    this->Jump = _jump;
    this->Skip = _skip;
    this->Side = _side;

}


//Liberer les Recources
void Classifier::Liberer(){

    delete(Walk);
    delete(Run);
    delete(Skip);
    delete(Side);
    delete(Jump);

    delete(Bend);
    delete(Wave1);
    delete(Wave2);
    delete(Jack);
    delete(Pjump);

}
