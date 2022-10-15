#include "crossvalidation.h"

/*
 * Class Pour Calculer le Taux de Reconnaissance
 * Du Modele
 * */

CrossValidation::CrossValidation(QString fileNameInPlace, QString fileNameNoPlace, Settings *setInplace, Settings *setNoplace)
{

    this->fileNameInPlace = fileNameInPlace;
    this->fileNameNoPlace = fileNameNoPlace;

    this->setInplace = setInplace;
    this->setNoplace = setNoplace;

    this->clsInplace = new Classifier(fileNameInPlace);
    this->clsNoplace = new Classifier(fileNameNoPlace);

    clsInplace->GetAllFeaturesWithoutDistances();
    clsNoplace->GetAllFeaturesWithoutDistances();

}


// Calculer le Taux de reconnaissance de la Base (profile)
double CrossValidation::PerformeAllTest(){


    Taux1 = PerformTest(clsInplace->Bend->mouvementMEI, clsInplace->Bend->mouvementMHI,"Bend",false,0,fileNameInPlace);
    Taux1 += PerformTest(clsInplace->Jack->mouvementMEI, clsInplace->Jack->mouvementMHI,"Jack",false,1,fileNameInPlace);
    Taux1 += PerformTest(clsInplace->Pjump->mouvementMEI, clsInplace->Pjump->mouvementMHI,"Pjump",false,2,fileNameInPlace);
    Taux1 += PerformTest(clsInplace->Wave1->mouvementMEI, clsInplace->Wave1->mouvementMHI,"Wave1",false,3,fileNameInPlace);
    Taux1 += PerformTest(clsInplace->Wave2->mouvementMEI, clsInplace->Wave2->mouvementMHI,"Wave2",false,4,fileNameInPlace);

    Taux2 = PerformTest(clsNoplace->Walk->mouvementMEI, clsNoplace->Walk->mouvementMHI,"Walk",true,5,fileNameNoPlace);
    Taux2 += PerformTest(clsNoplace->Jump->mouvementMEI, clsNoplace->Jump->mouvementMHI,"Jump",true,6,fileNameNoPlace);
    Taux2 += PerformTest(clsNoplace->Run->mouvementMEI, clsNoplace->Run->mouvementMHI,"Run",true,7,fileNameNoPlace);
    Taux2 += PerformTest(clsNoplace->Side->mouvementMEI, clsNoplace->Side->mouvementMHI,"Side",true,8,fileNameNoPlace);
    Taux2 += PerformTest(clsNoplace->Skip->mouvementMEI, clsNoplace->Skip->mouvementMHI,"Skip",true,9,fileNameNoPlace); 

    qDebug(QString::number(Taux1).toUtf8());
    qDebug(QString::number(Taux2).toUtf8());

    clsInplace->Liberer();
    clsNoplace->Liberer();

    delete(this->clsInplace);
    delete(this->clsNoplace);

    return ((Taux1/5)+(Taux2/5))/2;

}

double CrossValidation::PerformePlaceTest(){


    Taux1 = PerformTest(clsInplace->Bend->mouvementMEI, clsInplace->Bend->mouvementMHI,"Bend",false,0,fileNameInPlace);
    Taux1 += PerformTest(clsInplace->Jack->mouvementMEI, clsInplace->Jack->mouvementMHI,"Jack",false,1,fileNameInPlace);
    Taux1 += PerformTest(clsInplace->Pjump->mouvementMEI, clsInplace->Pjump->mouvementMHI,"Pjump",false,2,fileNameInPlace);
    Taux1 += PerformTest(clsInplace->Wave1->mouvementMEI, clsInplace->Wave1->mouvementMHI,"Wave1",false,3,fileNameInPlace);
    Taux1 += PerformTest(clsInplace->Wave2->mouvementMEI, clsInplace->Wave2->mouvementMHI,"Wave2",false,4,fileNameInPlace);

    if(setInplace->isMEI && setInplace->isMHI){

        preTaux1 = PerformNewTest(clsInplace->Bend->mouvementMEI, clsInplace->Bend->mouvementMHI,"Bend",false,0,fileNameInPlace);
        preTaux1 += PerformNewTest(clsInplace->Jack->mouvementMEI, clsInplace->Jack->mouvementMHI,"Jack",false,1,fileNameInPlace);
        preTaux1 += PerformNewTest(clsInplace->Pjump->mouvementMEI, clsInplace->Pjump->mouvementMHI,"Pjump",false,2,fileNameInPlace);
        preTaux1 += PerformNewTest(clsInplace->Wave1->mouvementMEI, clsInplace->Wave1->mouvementMHI,"Wave1",false,3,fileNameInPlace);
        preTaux1 += PerformNewTest(clsInplace->Wave2->mouvementMEI, clsInplace->Wave2->mouvementMHI,"Wave2",false,4,fileNameInPlace);

    }


    qDebug(QString::number(Taux1).toUtf8());

    clsInplace->Liberer();
    clsNoplace->Liberer();

    delete(this->clsInplace);
    delete(this->clsNoplace);

    return Taux1/5;

}

double CrossValidation::PerformeNoPlaceTest(){


    Taux2 = PerformTest(clsNoplace->Walk->mouvementMEI, clsNoplace->Walk->mouvementMHI,"Walk",true,5,fileNameNoPlace);
    Taux2 += PerformTest(clsNoplace->Jump->mouvementMEI, clsNoplace->Jump->mouvementMHI,"Jump",true,6,fileNameNoPlace);
    Taux2 += PerformTest(clsNoplace->Run->mouvementMEI, clsNoplace->Run->mouvementMHI,"Run",true,7,fileNameNoPlace);
    Taux2 += PerformTest(clsNoplace->Side->mouvementMEI, clsNoplace->Side->mouvementMHI,"Side",true,8,fileNameNoPlace);
    Taux2 += PerformTest(clsNoplace->Skip->mouvementMEI, clsNoplace->Skip->mouvementMHI,"Skip",true,9,fileNameNoPlace);

    if(setNoplace->isMEI && setNoplace->isMHI){

        preTaux2 = PerformNewTest(clsNoplace->Walk->mouvementMEI, clsNoplace->Walk->mouvementMHI,"Walk",true,5,fileNameNoPlace);
        preTaux2 += PerformNewTest(clsNoplace->Jump->mouvementMEI, clsNoplace->Jump->mouvementMHI,"Jump",true,6,fileNameNoPlace);
        preTaux2 += PerformNewTest(clsNoplace->Run->mouvementMEI, clsNoplace->Run->mouvementMHI,"Run",true,7,fileNameNoPlace);
        preTaux2 += PerformNewTest(clsNoplace->Side->mouvementMEI, clsNoplace->Side->mouvementMHI,"Side",true,8,fileNameNoPlace);
        preTaux2 += PerformNewTest(clsNoplace->Skip->mouvementMEI, clsNoplace->Skip->mouvementMHI,"Skip",true,9,fileNameNoPlace);

    }

    qDebug(QString::number(Taux2).toUtf8());

    clsInplace->Liberer();
    clsNoplace->Liberer();

    delete(this->clsInplace);
    delete(this->clsNoplace);

    return Taux2/5;

}

double CrossValidation::PerformTest(std::vector<std::vector<double>> toTestMEI, std::vector<std::vector<double>> toTestMHI, QString MvtName , bool isMoving , int choice,QString fileName){

    double GlobalTests = 0;
    double CorrectTests = 0;

    if(toTestMEI.empty())
        return 0;

    for(int i = 0 ; i < toTestMEI.size() ; i++){

        Classifier *tempClassifier = new Classifier(fileName,toTestMEI[i],toTestMHI[i]);
        tempClassifier->GetAllFeatures();

        switch(choice){
        case 0:
            tempClassifier->Bend->ForBypass(i);
            break;
        case 1:
            tempClassifier->Jack->ForBypass(i);
            break;
        case 2:
            tempClassifier->Pjump->ForBypass(i);
            break;
        case 3:
            tempClassifier->Wave1->ForBypass(i);
            break;
        case 4:
            tempClassifier->Wave2->ForBypass(i);
            break;
        case 5:
            tempClassifier->Walk->ForBypass(i);
            break;
        case 6:
            tempClassifier->Jump->ForBypass(i);
            break;
        case 7:
            tempClassifier->Run->ForBypass(i);
            break;
        case 8:
            tempClassifier->Side->ForBypass(i);
            break;
        case 9:
            tempClassifier->Skip->ForBypass(i);
            break;
        }



        QString Mvt;
        Recognize *rec = new Recognize(fileName);

        if(!isMoving){

            if(setInplace->isMEI && setInplace->isMHI){

                int **Matrix;

                if(setInplace->isprioMEI){

                    Matrix = tempClassifier->MatrixInPlace_MEI();
                    Mvt = rec->FinalChoosing(Matrix,*tempClassifier,true,false);

                }else{

                    Matrix = tempClassifier->MatrixInPlace_MHI();
                    Mvt = rec->FinalChoosingNEW(Matrix,*tempClassifier,true,false);

                }

            }else if(setInplace->isMEI){

                int **Matrix = tempClassifier->MatrixInPlace_MEI();
                Mvt = rec->FinalChoosing(Matrix,*tempClassifier,false,false);

            }else{

                int **Matrix = tempClassifier->MatrixInPlace_MHI();
                Mvt = rec->FinalChoosing(Matrix,*tempClassifier,false,false);

            }

        }else{


            if(setNoplace->isMEI && setNoplace->isMHI){

                int **Matrix;

                if(setNoplace->isprioMEI){

                    Matrix = tempClassifier->MatrixNoPlace_MEI();
                    Mvt = rec->FinalChoosing(Matrix,*tempClassifier,true,true);

                }else{

                    Matrix = tempClassifier->MatrixNoPlace_MHI();
                    Mvt = rec->FinalChoosingNEW(Matrix,*tempClassifier,true,true);

                }

            }else if(setNoplace->isMEI){

                int **Matrix = tempClassifier->MatrixNoPlace_MEI();
                Mvt = rec->FinalChoosing(Matrix,*tempClassifier,false,true);

            }else{

                int **Matrix = tempClassifier->MatrixNoPlace_MHI();
                Mvt = rec->FinalChoosing(Matrix,*tempClassifier,false,true);

            }


        }

        if(Mvt.compare(MvtName) == 0)
            CorrectTests++;

        GlobalTests++;

        qDebug(Mvt.toUtf8());

        tempClassifier->Liberer();

        delete(tempClassifier);
        delete(rec);
    }

    qDebug("--------------------");

    return CorrectTests/GlobalTests;

}

// Effacer une valeur
std::vector<std::vector<double>> CrossValidation::ByPass(std::vector<std::vector<double>> V, int j){

    std::vector<std::vector<double>> newVec;

    for(int i = 0; i < V.size() ; i++){

        if(i == j)
            continue;

        newVec.push_back(V[i]);

    }

    return newVec;

}

double CrossValidation::PerformNewTest(std::vector<std::vector<double>> toTestMEI, std::vector<std::vector<double>> toTestMHI, QString MvtName , bool isMoving , int choice,QString fileName){

    double GlobalTests = 0;
    double CorrectTests = 0;

    if(toTestMEI.empty())
        return 0;

    for(int i = 0 ; i < toTestMEI.size() ; i++){

        Classifier *tempClassifier = new Classifier(fileName,toTestMEI[i],toTestMHI[i]);
        tempClassifier->GetAllFeatures();

        switch(choice){
        case 0:
            tempClassifier->Bend->ForBypass(i);
            break;
        case 1:
            tempClassifier->Jack->ForBypass(i);
            break;
        case 2:
            tempClassifier->Pjump->ForBypass(i);
            break;
        case 3:
            tempClassifier->Wave1->ForBypass(i);
            break;
        case 4:
            tempClassifier->Wave2->ForBypass(i);
            break;
        case 5:
            tempClassifier->Walk->ForBypass(i);
            break;
        case 6:
            tempClassifier->Jump->ForBypass(i);
            break;
        case 7:
            tempClassifier->Run->ForBypass(i);
            break;
        case 8:
            tempClassifier->Side->ForBypass(i);
            break;
        case 9:
            tempClassifier->Skip->ForBypass(i);
            break;
        }

        Recognize *rec = new Recognize(fileName);

        bool isCorrect;

        if(!isMoving){

            int **Matrix;

            if(setInplace->isMEI && setInplace->isMHI){

                if(setInplace->isprioMEI){

                    Matrix = tempClassifier->MatrixInPlace_MEI();
                    isCorrect = rec->checkCheck(Matrix,*tempClassifier,false,MvtName);

                }else{

                    Matrix = tempClassifier->MatrixInPlace_MHI();
                    isCorrect = rec->checkCheck(Matrix,*tempClassifier,false,MvtName);

                }

            }



        }else{


            int **Matrix;

            if(setNoplace->isMEI && setNoplace->isMHI){

                if(setNoplace->isprioMEI){

                    Matrix = tempClassifier->MatrixNoPlace_MEI();
                    isCorrect = rec->checkCheck(Matrix,*tempClassifier,true,MvtName);

                }else{

                    Matrix = tempClassifier->MatrixNoPlace_MHI();
                    isCorrect = rec->checkCheck(Matrix,*tempClassifier,true,MvtName);

                }

            }


        }

        if(isCorrect)
            CorrectTests++;

        GlobalTests++;

        tempClassifier->Liberer();

        delete(tempClassifier);
        delete(rec);
    }

    qDebug("--------------------");

    return CorrectTests/GlobalTests;

}


