#include "recognize.h"

/*
 * Class Pour Enregister les Information des Moments de Tchibychev
 * Sur des Fichiers
 * */

//Des Verifications
Recognize::Recognize(QString fileName)
{

    this->fileName = fileName;

    QStringList temp = fileName.split("/");

    if(!QDir(fileName).exists()){
        QDir().mkpath(fileName);
    }

    if(!QDir(temp.at(0)+"/MEI_MHI").exists()){
        QDir().mkdir(temp.at(0)+"/MEI_MHI");
    }

    if(!QDir(temp.at(0)+"/MEI_MHI/Walk").exists()){
        QDir().mkdir(temp.at(0)+"/MEI_MHI/Walk");
    }

    if(!QDir(temp.at(0)+"/MEI_MHI/Run").exists()){
        QDir().mkdir(temp.at(0)+"/MEI_MHI/Run");
    }

    if(!QDir(temp.at(0)+"/MEI_MHI/Jump").exists()){
        QDir().mkdir(temp.at(0)+"/MEI_MHI/Jump");
    }

    if(!QDir(temp.at(0)+"/MEI_MHI/Side").exists()){
        QDir().mkdir(temp.at(0)+"/MEI_MHI/Side");
    }

    if(!QDir(temp.at(0)+"/MEI_MHI/Skip").exists()){
        QDir().mkdir(temp.at(0)+"/MEI_MHI/Skip");
    }

    if(!QDir(temp.at(0)+"/MEI_MHI/Bend").exists()){
        QDir().mkdir(temp.at(0)+"/MEI_MHI/Bend");
    }

    if(!QDir(temp.at(0)+"/MEI_MHI/Jack").exists()){
        QDir().mkdir(temp.at(0)+"/MEI_MHI/Jack");
    }

    if(!QDir(temp.at(0)+"/MEI_MHI/Wave1").exists()){
        QDir().mkdir(temp.at(0)+"/MEI_MHI/Wave1");
    }

    if(!QDir(temp.at(0)+"/MEI_MHI/Wave2").exists()){
        QDir().mkdir(temp.at(0)+"/MEI_MHI/Wave2");
    }

    if(!QDir(temp.at(0)+"/MEI_MHI/Pjump").exists()){
        QDir().mkdir(temp.at(0)+"/MEI_MHI/Pjump");
    }

    if(!QDir(fileName+"/INPLACE").exists()){
        QDir().mkdir(fileName+"/INPLACE");
    }

    if(!QDir(fileName+"/NOPLACE").exists()){
        QDir().mkdir(fileName+"/NOPLACE");
    }

    if(!QFile(fileName+"/NOPLACE/Walk").exists()){
        QFile file(fileName+"/NOPLACE/Walk");
        file.open(QIODevice::ReadWrite);
        file.close();
    }

    if(!QFile(fileName+"/NOPLACE/Run").exists()){
        QFile file(fileName+"/NOPLACE/Run");
        file.open(QIODevice::ReadWrite);
        file.close();
    }

    if(!QFile(fileName+"/NOPLACE/Side").exists()){
        QFile file(fileName+"/NOPLACE/Side");
        file.open(QIODevice::ReadWrite);
        file.close();
    }

    if(!QFile(fileName+"/NOPLACE/Jump").exists()){
        QFile file(fileName+"/NOPLACE/Jump");
        file.open(QIODevice::ReadWrite);
        file.close();
    }

    if(!QFile(fileName+"/NOPLACE/Skip").exists()){
        QFile file(fileName+"/NOPLACE/Skip");
        file.open(QIODevice::ReadWrite);
        file.close();
    }

    if(!QFile(fileName+"/INPLACE/Bend").exists()){
        QFile file(fileName+"/INPLACE/Bend");
        file.open(QIODevice::ReadWrite);
        file.close();
    }

    if(!QFile(fileName+"/INPLACE/Pjump").exists()){
        QFile file(fileName+"/INPLACE/Pjump");
        file.open(QIODevice::ReadWrite);
        file.close();
    }

    if(!QFile(fileName+"/INPLACE/Wave1").exists()){
        QFile file(fileName+"/INPLACE/Wave1");
        file.open(QIODevice::ReadWrite);
        file.close();
    }

    if(!QFile(fileName+"/INPLACE/Wave2").exists()){
        QFile file(fileName+"/INPLACE/Wave2");
        file.open(QIODevice::ReadWrite);
        file.close();
    }

    if(!QFile(fileName+"/NOPLACE/Jack").exists()){
        QFile file(fileName+"/INPLACE/Jack");
        file.open(QIODevice::ReadWrite);
        file.close();
    }

}

bool Recognize::Checkbyname(QString filename, QString name){

    QFile file(filename);
    file.open(QIODevice::ReadOnly);

    QTextStream in(&file);

    while(!in.atEnd()){

        QString line = in.readLine();
        QStringList list = line.split(":");

        if(name.compare(list.at(0)) == 0)
            return true;

    }

    file.close();

    return false;

}


//Pour verifier si l'information exist deja dans la base
int Recognize::CheckIfExist(QString filename, std::vector<double> infos){

    QFile file(filename);
    file.open(QIODevice::ReadOnly);

    QTextStream in(&file);

    std::vector<double> tempVec;

    int lines = 0;
    bool bypassFirst;

    while(!in.atEnd()){

        QString line = in.readLine();

        bypassFirst = true;

        lines++;

        if(lines%2 == 0)
            continue;

        QStringList list = line.split(":");

        foreach(QString info , list){

            if(bypassFirst){
                bypassFirst = false;
                continue;
            }

            tempVec.push_back(info.toDouble());

        }

        int counter = 0;

        for(int i = 0 ; i < tempVec.size() ; i++){

            if(tempVec[i] == infos[i])
                counter++;

        }

        if(counter == infos.size())
            return lines;

        tempVec.clear();

    }

    return 0;

}

bool Recognize::Supprimer(QString filename, QString name){


    QFile file(filename);
    file.open(QIODevice::ReadOnly);

    QTextStream in(&file);

    QFile toCopy(filename+"temp");
    toCopy.open(QIODevice::ReadWrite);
    toCopy.close();

    bool bypassFirst = true;

    while(!in.atEnd()){

        QString line = in.readLine();

        bypassFirst = true;

        QStringList list = line.split(":");

        if(name.compare(list.at(0)) != 0){

            std::vector<double> tempVec;

            foreach(QString info , list){

                if(bypassFirst){
                    bypassFirst = false;
                    continue;
                }

                tempVec.push_back(info.toDouble());

            }

            AppendInFile(filename+"temp",list.at(0), tempVec, true);

        }




    }

    file.remove();
    file.close();

    toCopy.rename(filename);
    toCopy.close();

    return true;

}

//Ajouter Information dans La Fin du Video
bool Recognize::AppendInFile(QString filename, QString name , std::vector<double> infos, bool forceAppend){

    if(CheckIfExist(filename,infos) != 0 && !forceAppend){
        return false;
    }

    QFile file(filename);
    file.open(QIODevice::Append);
    QString toWrite = name+":";
    for(int i = 0 ; i < infos.size() ; i++){
        if(i == infos.size()-1){
            toWrite += (QString::number(infos[i], 'g', 64)+"\n");
        }else{
            toWrite += (QString::number(infos[i], 'g', 64)+":");
        }
    }

    file.write(toWrite.toUtf8());
    file.close();

    return true;

}

//Ajouter l'info
bool Recognize::addInfo(int choice,QString name, std::vector<double> infos,bool forceAppend){

    switch (choice) {
    case 0:
        // Jump
        return AppendInFile(fileName+"/NOPLACE/Jump",name,infos,forceAppend);
        break;
    case 1:
        // Run
        return AppendInFile(fileName+"/NOPLACE/Run",name,infos,forceAppend);
        break;
    case 2:
        // Side
        return AppendInFile(fileName+"/NOPLACE/Side",name,infos,forceAppend);
        break;
    case 3:
        // Skip
        return AppendInFile(fileName+"/NOPLACE/Skip",name,infos,forceAppend);
        break;
    case 4:
        // Walk
        return AppendInFile(fileName+"/NOPLACE/Walk",name,infos,forceAppend);
        break;
    case 5:
        // Bend
        return AppendInFile(fileName+"/INPLACE/Bend",name,infos,forceAppend);
        break;
    case 6:
        // Jack
        return AppendInFile(fileName+"/INPLACE/Jack",name,infos,forceAppend);
        break;
    case 7:
        //Pjump
        return AppendInFile(fileName+"/INPLACE/Pjump",name,infos,forceAppend);
        break;
    case 8:
        //Wave1
        return AppendInFile(fileName+"/INPLACE/Wave1",name,infos,forceAppend);
        break;
    case 9:
        //Wave2
        return AppendInFile(fileName+"/INPLACE/Wave2",name,infos,forceAppend);
        break;

    }

    return false;

}


//Pour Choisir les Meilleur 3 Mouvement Avec Les MEI
Params* Recognize::Choosing(int **choices , Classifier cls,bool isMoving){

    int counter;
    int counters[5][2];

    for (int i = 0; i < 5; i++) {

        counter = 0;

        for (int j = 0; j < 5; j++) {

            if (choices[j][i] == 1) {
                counter++;
            }

        }

        counters[i][0] = counter;
        counters[i][1] = i;

    }


    //trie
    for (int i = 0; i < 5; i++) {

        for (int j = 0; j < 5 - 1; j++) {

            int x[2];
            if (counters[j + 1][0] > counters[j][0]) {

                x[0] = counters[j + 1][0];
                x[1] = counters[j + 1][1];

                counters[j + 1][0] = counters[j][0];
                counters[j + 1][1] = counters[j][1];

                counters[j][0] = x[0];
                counters[j][1] = x[1];

            }

        }

    }

    Params *params = new Params[3];

    int mouvement;
    PreClassification = "";

    if(isMoving){

        for (int i = 0; i < 3; i++) {
            mouvement = counters[i][1];

            switch (mouvement) {
            case 0:
                params[i].V = cls.Walk->distanceMHI;
                params[i].i = 0;
                PreClassification += "Walk\n";
                break;

            case 1:
                params[i].V = cls.Run->distanceMHI;
                params[i].i = 1;
                PreClassification += "Run\n";
                break;

            case 2:
                params[i].V = cls.Jump->distanceMHI;
                params[i].i = 2;
                PreClassification += "Jump\n";
                break;

            case 3:
                params[i].V = cls.Skip->distanceMHI;
                params[i].i = 3;
                PreClassification += "Skip\n";
                break;

            case 4:
                params[i].V = cls.Side->distanceMHI;
                params[i].i = 4;
                PreClassification += "Side\n";
                break;

            }

        }

    }else{

        for (int i = 0; i < 3; i++) {
            mouvement = counters[i][1];

            switch (mouvement) {
            case 0:
                params[i].V = cls.Bend->distanceMHI;
                params[i].i = 0;
                PreClassification += "Bend\n";
                break;

            case 1:
                params[i].V = cls.Jack->distanceMHI;
                params[i].i = 1;
                PreClassification += "Jack\n";
                break;

                case 2:
                params[i].V = cls.Pjump->distanceMHI;
                params[i].i = 2;
                PreClassification += "Pjump\n";
                break;

            case 3:
                params[i].V = cls.Wave1->distanceMHI;
                params[i].i = 3;
                PreClassification += "Wave1\n";
                break;

            case 4:
                params[i].V = cls.Wave2->distanceMHI;
                params[i].i = 4;
                PreClassification += "Wave2\n";
                break;

            }

        }
    }

    return params;

}

// Retourne le Nom du Mouvement Sur cette fonction en utilise la fonction Choosing
QString Recognize::FinalChoosing(int **choices , Classifier cls, bool isPoweredUP, bool isMoving){

    if(!isPoweredUP){

        if(isMoving){

            Params *params = Choosing(choices,cls,true);

            int mouvement = params[0].i;

            switch (mouvement) {
            case 0:
                return "Walk";

            case 1:
                return "Run";

            case 2:
                return "Jump";

            case 3:
                return "Skip";

            case 4:
                return "Side";

            }

        }else{

            Params *params = Choosing(choices,cls,false);

            int mouvement = params[0].i;

            switch (mouvement) {
            case 0:
                return "Bend";
            case 1:
                return "Jack";

            case 2:
                return "Pjump";

            case 3:
                return "Wave1";

            case 4:
                return "Wave2";

            }

        }

    }else{

        Params *params = Choosing(choices,cls,isMoving);

        delete(choices);

        return PowerUp(params,isMoving);

    }

    return "NaN";

}



//Fonction Pour Calculer le Meilleur Mouvement entre 3 Mouvement Utilisant les MHI
QString Recognize::PowerUp(Params *params, bool isMoving){

    int pChoices[3][3];

    Classifier *cls = new Classifier();

    pChoices[0][0] = cls->nearestN(params[0].V, params[1].V);
    pChoices[1][0] = cls->nearestN(params[0].V, params[2].V);
    pChoices[2][0] = 1;

    pChoices[0][1] = cls->nearestN(params[1].V, params[0].V);
    pChoices[1][1] = cls->nearestN(params[1].V, params[2].V);
    pChoices[2][1] = 1;

    pChoices[0][2] = cls->nearestN(params[2].V, params[0].V);
    pChoices[1][2] = cls->nearestN(params[2].V, params[1].V);
    pChoices[2][2] = 1;

    int counter;
    int counters[3][2];

    for (int i = 0; i < 3; i++) {

        counter = 0;

        for (int j = 0; j < 3; j++) {

            if (pChoices[j][i] == 1) {
                counter++;
            }

        }

        counters[i][0] = counter;
        counters[i][1] = params[i].i;

    }

    for (int i = 0; i < 3; i++) {

        for (int j = 0; j < 3 - 1; j++) {

            int x[2];
            if (counters[j + 1][0] > counters[j][0]) {

                x[0] = counters[j + 1][0];
                x[1] = counters[j + 1][1];

                counters[j + 1][0] = counters[j][0];
                counters[j + 1][1] = counters[j][1];

                counters[j][0] = x[0];
                counters[j][1] = x[1];

            }

        }

    }

    int mouvement = counters[0][1];

    if(isMoving){

        switch (mouvement) {
        case 0:
            return"Walk";

        case 1:
            return "Run";

        case 2:
            return "Jump";

        case 3:
            return "Skip";

        case 4:
            return "Side";

        }

    }else{

        switch (mouvement) {
        case 0:
            return "Bend";

        case 1:
            return "Jack";

        case 2:
            return "Pjump";

        case 3:
            return "Wave1";

        case 4:
            return "Wave2";

        }

    }

    return "NaN";

}


bool Recognize::checkCheck(int **choices , Classifier cls,bool isMoving, QString Name){

    Params *params = Choosing(choices,cls,isMoving);

    QStringList list = PreClassification.split("\n");

    for(QString mvt : list){

        if(mvt.compare(Name) == 0)
            return true;

    }

    return false;


}


//Pour Choisir les Meilleur 3 Mouvement Avec Les MEI
Params* Recognize::ChoosingNEW(int **choices , Classifier cls,bool isMoving){

    int counter;
    int counters[5][2];

    for (int i = 0; i < 5; i++) {

        counter = 0;

        for (int j = 0; j < 5; j++) {

            if (choices[j][i] == 1) {
                counter++;
            }

        }

        counters[i][0] = counter;
        counters[i][1] = i;

    }


    //trie
    for (int i = 0; i < 5; i++) {

        for (int j = 0; j < 5 - 1; j++) {

            int x[2];
            if (counters[j + 1][0] > counters[j][0]) {

                x[0] = counters[j + 1][0];
                x[1] = counters[j + 1][1];

                counters[j + 1][0] = counters[j][0];
                counters[j + 1][1] = counters[j][1];

                counters[j][0] = x[0];
                counters[j][1] = x[1];

            }

        }

    }

    Params *params = new Params[3];

    int mouvement;
    PreClassification = "";

    if(isMoving){

        for (int i = 0; i < 3; i++) {
            mouvement = counters[i][1];

            switch (mouvement) {
            case 0:
                params[i].V = cls.Walk->distanceMEI;
                params[i].i = 0;
                PreClassification += "Walk\n";
                break;

            case 1:
                params[i].V = cls.Run->distanceMEI;
                params[i].i = 1;
                PreClassification += "Run\n";
                break;

            case 2:
                params[i].V = cls.Jump->distanceMEI;
                params[i].i = 2;
                PreClassification += "Jump\n";
                break;

            case 3:
                params[i].V = cls.Skip->distanceMEI;
                params[i].i = 3;
                PreClassification += "Skip\n";
                break;

            case 4:
                params[i].V = cls.Side->distanceMEI;
                params[i].i = 4;
                PreClassification += "Side\n";
                break;

            }

        }

    }else{

        for (int i = 0; i < 3; i++) {
            mouvement = counters[i][1];

            switch (mouvement) {
            case 0:
                params[i].V = cls.Bend->distanceMEI;
                params[i].i = 0;
                PreClassification += "Bend\n";
                break;

            case 1:
                params[i].V = cls.Jack->distanceMEI;
                params[i].i = 1;
                PreClassification += "Jack\n";
                break;

                case 2:
                params[i].V = cls.Pjump->distanceMEI;
                params[i].i = 2;
                PreClassification += "Pjump\n";
                break;

            case 3:
                params[i].V = cls.Wave1->distanceMEI;
                params[i].i = 3;
                PreClassification += "Wave1\n";
                break;

            case 4:
                params[i].V = cls.Wave2->distanceMEI;
                params[i].i = 4;
                PreClassification += "Wave2\n";
                break;

            }

        }
    }

    return params;

}


// Retourne le Nom du Mouvement Sur cette fonction en utilise la fonction Choosing
QString Recognize::FinalChoosingNEW(int **choices , Classifier cls, bool isPoweredUP, bool isMoving){

    if(!isPoweredUP){

        if(isMoving){

            Params *params = ChoosingNEW(choices,cls,true);

            int mouvement = params[0].i;

            switch (mouvement) {
            case 0:
                return "Walk";

            case 1:
                return "Run";

            case 2:
                return "Jump";

            case 3:
                return "Skip";

            case 4:
                return "Side";

            }

        }else{

            Params *params = ChoosingNEW(choices,cls,false);

            int mouvement = params[0].i;

            switch (mouvement) {
            case 0:
                return "Bend";
            case 1:
                return "Jack";

            case 2:
                return "Pjump";

            case 3:
                return "Wave1";

            case 4:
                return "Wave2";

            }

        }

    }else{

        Params *params = ChoosingNEW(choices,cls,isMoving);

        delete(choices);

        return PowerUp(params,isMoving);

    }

    return "NaN";

}
