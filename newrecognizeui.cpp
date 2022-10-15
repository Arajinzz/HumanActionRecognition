#include "newrecognizeui.h"
#include "ui_newrecognizeui.h"

#include "mainwindow.h"

newRecognizeUI::newRecognizeUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::newRecognizeUI)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this);
    vw = new QVideoWidget(this);
    vw->setStyleSheet("background-color: black");

    player->setVideoOutput(vw);

    ui->verticalLayout->addWidget(vw);

    slider = new QSlider(this);
    slider->setOrientation(Qt::Horizontal);

    ui->verticalLayout->addWidget(slider);

    connect(player,&QMediaPlayer::durationChanged,slider,&QSlider::setMaximum);
    connect(player,&QMediaPlayer::positionChanged,slider,&QSlider::setValue);

    connect(slider,&QSlider::sliderMoved,player,&QMediaPlayer::setPosition);

    ui->tabWidget->setCurrentIndex(0);

    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("P"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Q"));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("MEI"));
    ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("MHI"));

    ui->tableWidget_2->setHorizontalHeaderItem(0, new QTableWidgetItem("P"));
    ui->tableWidget_2->setHorizontalHeaderItem(1, new QTableWidgetItem("Q"));
    ui->tableWidget_2->setHorizontalHeaderItem(2, new QTableWidgetItem("MEI"));
    ui->tableWidget_2->setHorizontalHeaderItem(3, new QTableWidgetItem("MHI"));

    currentInPlaceOrder = 10;
    currentNoPlaceOrder = 10;

    ui->warningM->setVisible(false);
    ui->warningM_2->setVisible(false);

    this->setAttribute(Qt::WA_DeleteOnClose);

}

newRecognizeUI::~newRecognizeUI()
{
    delete ui;
}

void newRecognizeUI::on_play_clicked()
{

    switch (player->state()) {
    case QMediaPlayer::PlayingState:
        player->pause();
        break;
    default:
        player->play();
        break;
    }

}


void newRecognizeUI::on_stop_clicked()
{

    player->stop();
    player->setPosition(0);

}

void newRecognizeUI::showBase(){

    ui->listWidget->clear();

    QFile file(currentFile);
    file.open(QIODevice::ReadOnly);

    QTextStream in(&file);

    bool escape = false;

    while(!in.atEnd()){

        QString line = in.readLine();
        QStringList list = line.split(":");

        if(escape){
            escape = false;
            continue;
        }else{
            escape = true;
        }

        ui->listWidget->addItem(list.at(0));

    }

}

void newRecognizeUI::ShowTable(QString toShow, QTableWidget *table, int order, bool isMethode1){

    table->clear();
    table->setRowCount(0);

    table->setHorizontalHeaderItem(0, new QTableWidgetItem("P"));
    table->setHorizontalHeaderItem(1, new QTableWidgetItem("Q"));
    table->setHorizontalHeaderItem(2, new QTableWidgetItem("MEI"));
    table->setHorizontalHeaderItem(3, new QTableWidgetItem("MHI"));

    QFile file(currentFile);
    file.open(QIODevice::ReadOnly);

    QTextStream in(&file);

    int i = 0;
    int p = 0;
    int q = 0;

    bool breakALL = false;

    while(!in.atEnd()){

        QString line1 = in.readLine();
        QStringList list1 = line1.split(":");

        QString line2 = in.readLine();
        QStringList list2 = line2.split(":");

        p = 0;
        q = 0;

        for(int j = 0 ; j< list1.count() ; j++){

            if(j==0){

                if(toShow.compare(list1.at(0)) != 0)
                    break;
                else
                    breakALL = true;

                continue;

            }

            if(isMethode1){

                q = 0;

                while( p+q < order ){

                    q++;

                }

            }

            QTableWidgetItem* item1 = new QTableWidgetItem();
            item1->setText(QString::number(p));
            QTableWidgetItem* item2 = new QTableWidgetItem();
            item2->setText(QString::number(q));
            QTableWidgetItem* item3 = new QTableWidgetItem();
            item3->setText(list1.at(j));
            QTableWidgetItem* item4 = new QTableWidgetItem();
            item4->setText(list2.at(j));

            if(!isMethode1){

                if(p + q == order){
                    q=0;
                    p++;
                }else{
                    q++;
                }

            }else{

                p++;

            }

            table->insertRow(i);
            table->setItem(i, 0 ,item1);
            table->setItem(i, 1 ,item2);
            table->setItem(i, 2, item3);
            table->setItem(i, 3, item4);

            i++;


        }

        if(breakALL)
            break;

    }

}

void newRecognizeUI::LoadSettingsInPlace(){

    int tempOrd;

    if(setInplace != NULL)
        delete(setInplace);

    if(ui->ord0->isChecked())
        tempOrd = 0;
    else if(ui->ord1->isChecked())
        tempOrd = 1;
    else if(ui->ord2->isChecked())
        tempOrd = 2;
    else if(ui->ord3->isChecked())
        tempOrd = 3;
    else if(ui->ord4->isChecked())
        tempOrd = 4;
    else if(ui->ord5->isChecked())
        tempOrd = 5;
    else if(ui->ord6->isChecked())
        tempOrd = 6;
    else if(ui->ord7->isChecked())
        tempOrd = 7;
    else if(ui->ord8->isChecked())
        tempOrd = 8;
    else if(ui->ord9->isChecked())
        tempOrd = 9;
    else
        tempOrd = 10;

    this->setInplace = new Settings(45,40,6,tempOrd,ui->Meth1->isChecked(), ui->isMEI->isChecked() , ui->isMHI->isChecked(), ui->prioMEI_2->isChecked());

}


void newRecognizeUI::LoadSettingsNoPlace(){

    int tempOrd;

    if(setNoplace != NULL)
        delete(setNoplace);

    if(ui->ord0_2->isChecked())
        tempOrd = 0;
    else if(ui->ord1_2->isChecked())
        tempOrd = 1;
    else if(ui->ord2_2->isChecked())
        tempOrd = 2;
    else if(ui->ord3_2->isChecked())
        tempOrd = 3;
    else if(ui->ord4_2->isChecked())
        tempOrd = 4;
    else if(ui->ord5_2->isChecked())
        tempOrd = 5;
    else if(ui->ord6_2->isChecked())
        tempOrd = 6;
    else if(ui->ord7_2->isChecked())
        tempOrd = 7;
    else if(ui->ord8_2->isChecked())
        tempOrd = 8;
    else if(ui->ord9_2->isChecked())
        tempOrd = 9;
    else
        tempOrd = 10;

    this->setNoplace = new Settings(framesMEI,framesMHI,Var,tempOrd,ui->Meth1_2->isChecked(),ui->isMEI_2->isChecked() , ui->isMHI_2->isChecked(), ui->prioMEI->isChecked());

}


void newRecognizeUI::on_loadVideo_clicked()
{

    QString tempvideoFilename = QFileDialog::getOpenFileName(this,"Open a File : ","","Video File (*.avi)");

    if(!tempvideoFilename.toStdString().empty()){

        ui->preC->clear();
        ui->mvtname->clear();
        ui->tableWidget_2->clear();

        ui->tableWidget_2->setHorizontalHeaderItem(0, new QTableWidgetItem("P"));
        ui->tableWidget_2->setHorizontalHeaderItem(1, new QTableWidgetItem("Q"));
        ui->tableWidget_2->setHorizontalHeaderItem(2, new QTableWidgetItem("MEI"));
        ui->tableWidget_2->setHorizontalHeaderItem(3, new QTableWidgetItem("MHI"));

        videoFilename = tempvideoFilename;

        player->setMedia(QUrl::fromLocalFile(videoFilename));
        on_play_clicked();

        isVideoLoaded = true;

        VideoAnalysis video(videoFilename.toStdString());

        if(video.isMoving(false)){

            if(video.isMoving(true)){
                ui->typeMouvement->setText("Mouvement Avec Deplacement Direction : a Droite");
            }else{
                ui->typeMouvement->setText("Mouvement Avec Deplacement Direction : a Gauche");
            }


            ImageAnalysis *img1;
            ImageAnalysis *img2;

            if(this->BaseName.compare("Avec_Boite") == 0){
                video.centredMEI(setNoplace->framesMEI);
                img1 = new ImageAnalysis(image = video.Original.clone());
                video.centredMHI(255,setNoplace->Var,setNoplace->framesMHI);
                img2 = new ImageAnalysis(image = video.Original.clone());
            }else{
                video.GenerateMEI(setNoplace->framesMEI);
                img1 = new ImageAnalysis(image = video.Original.clone());
                video.GenerateMHI(setNoplace->framesMHI,255,setNoplace->Var);
                img2 = new ImageAnalysis(image = video.Original.clone());
            }

            img1->saveImage("loadMEI.png");
            img2->saveImage("loadMHI.png");

            QPixmap pix1("loadMEI.png");
            ui->MEIViewer1->setPixmap(pix1);
            ui->MEIViewer1->setScaledContents( true );
            ui->MEIViewer1 ->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

            QPixmap pix2("loadMHI.png");
            ui->MHIViewer1->setPixmap(pix2);
            ui->MHIViewer1->setScaledContents( true );
            ui->MHIViewer1 ->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );


        }else{

            ui->typeMouvement->setText("Mouvement Sans Deplacement");

            video.GenerateMEI(setInplace->framesMEI);
            ImageAnalysis img1(image = video.Original.clone());
            img1.saveImage("loadMEI.png");
            QPixmap pix1("loadMEI.png");
            ui->MEIViewer1->setPixmap(pix1);
            ui->MEIViewer1->setScaledContents( true );
            ui->MEIViewer1 ->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );


            video.GenerateMHI(setInplace->framesMHI,255,setInplace->Var);
            ImageAnalysis img2(image = video.Original.clone());
            img2.saveImage("loadMHI.png");
            QPixmap pix2("loadMHI.png");
            ui->MHIViewer1->setPixmap(pix2);
            ui->MHIViewer1->setScaledContents( true );
            ui->MHIViewer1 ->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );


        }


    }

}


//INIT
void newRecognizeUI::Init(QString BaseName, int framesMEI, int framesMHI, int Var, QWidget *mainWin){

    QMessageBox *msgBox1 = new QMessageBox;
    msgBox1->setText("In Progress.. Please Wait.");
    msgBox1->setWindowTitle("In Progress.. Please Wait.");
    msgBox1->setAttribute(Qt::WA_DeleteOnClose);
    msgBox1->setWindowModality(Qt::ApplicationModal);
    QCoreApplication::processEvents();
    msgBox1->show();
    QCoreApplication::processEvents();

    this->mainWin = mainWin;

    if(BaseName.compare("Sans_Boite") == 0){

        ui->ord9_2->setChecked(true);
        ui->Meth2_2->setChecked(true);
        ui->isMEI_2->setChecked(false);
        ui->isMHI_2->setChecked(true);

    }

    this->BaseName = BaseName;

    for(int i = 0 ; i < 11 ; i++){

        recList1[i] = new Recognize(this->BaseName+"/Methode1/Order"+QString::number(i));
        recList2[i] = new Recognize(this->BaseName+"/Methode2/Order"+QString::number(i));

    }

    this->framesMEI = framesMEI;
    this->framesMHI = framesMHI;
    this->Var = Var;

    LoadSettingsInPlace();
    LoadSettingsNoPlace();

    if(setInplace->isMEI == false || setInplace->isMHI == false){
        ui->prioMEI_2->setDisabled(true);
        ui->prioMHI_2->setDisabled(true);
    }else{
        ui->prioMEI_2->setDisabled(false);
        ui->prioMHI_2->setDisabled(false);
    }

    if(setNoplace->isMEI == false || setNoplace->isMHI == false){
        ui->prioMEI->setDisabled(true);
        ui->prioMHI->setDisabled(true);
    }else{
        ui->prioMEI->setDisabled(false);
        ui->prioMHI->setDisabled(false);
    }

    this->prevSetInPlace = new Settings(setInplace->framesMEI, setInplace->framesMHI, setInplace->Var, setInplace->Ord, setInplace->isMethode1, setInplace->isMEI , setInplace->isMHI, setInplace->isprioMEI);
    this->prevSetNoPlace = new Settings(setNoplace->framesMEI, setNoplace->framesMHI, setNoplace->Var, setNoplace->Ord, setNoplace->isMethode1, setNoplace->isMEI , setNoplace->isMHI, setNoplace->isprioMEI);

    if(BaseName.compare("Avec_Boite") == 0){
        this->setWindowTitle("Reconnaissance Avec Boite Englobante");
    }else{
        this->setWindowTitle("Reconnaissance Sans Boite Englobante");
    }


    on_tabWidget_tabBarClicked(0);

    currentFile = this->BaseName+"/Methode2/Order10/NOPLACE/Walk";
    showBase();


    msgBox1->close();

}


void newRecognizeUI::on_addV_clicked()
{

    if(!isVideoLoaded && dialogsON){
        QMessageBox::critical(
            this,
            tr("Error"),
            tr("Svp Charger une Video"));
        return;
    }

    QString FN = videoFilename.split("/").last();

    if(dialogsON){

        bool ok;

        FN = QInputDialog::getText(0, "Input",
                                       "Donner le Nom du Video :", QLineEdit::Normal,
                                        "", &ok);

        while(FN.isEmpty()){

            FN = QInputDialog::getText(0, "Erreur",
                                           "Donner un Nom du Valid :", QLineEdit::Normal,
                                            "", &ok);
        }

    }

    while(recList1[0]->Checkbyname(currentFile,FN)){

        FN = FN + "(Cpy)";

    }

    QMessageBox *msgBox1 = new QMessageBox;
    msgBox1->setText("In Progress.. Please Wait.");
    msgBox1->setWindowTitle("In Progress.. Please Wait.");
    msgBox1->setAttribute(Qt::WA_DeleteOnClose);
    msgBox1->setWindowModality(Qt::ApplicationModal);
    QCoreApplication::processEvents();
    msgBox1->show();
    QCoreApplication::processEvents();


    //I NEED OPTIMISATION BE RIGHT BACK

    bool isAdded;
    int choice;

    std::string cvt = videoFilename.toUtf8().constData();

    std::vector<double> featuresMEI;
    std::vector<double> featuresMHI;
    ImageAnalysis *imgMEI;
    ImageAnalysis *imgMHI;

    //Si on a choisie un Video
    if(!cvt.empty()){

        VideoAnalysis video(cvt);
        cv::Mat MEI,MHI;

        // Recuperer MEI et MHI
        if(video.isMoving(false)){

            if(this->BaseName.compare("Avec_Boite") == 0){
                MEI = video.centredMEI(setNoplace->framesMEI).clone();
                MHI = video.centredMHI(255,setNoplace->Var,setNoplace->framesMHI).clone();
            }else{
                MEI = video.GenerateMEI(setNoplace->framesMEI).clone();
                MHI = video.GenerateMHI(setNoplace->framesMHI,255,setNoplace->Var).clone();
            }

        }else{

           MEI = video.GenerateMEI(setInplace->framesMEI).clone();
           MHI = video.GenerateMHI(setInplace->framesMHI,255,setInplace->Var).clone();

        }

        imgMEI = new ImageAnalysis(MEI.clone());
        imgMHI = new ImageAnalysis(MHI.clone());

        ImageAnalysis imgMEI(MEI);
        ImageAnalysis imgMHI(MHI);

        //Recuperer les Moments de Tchibychev
        featuresMEI = imgMEI.MomentVector(10, false, false);
        featuresMHI = imgMHI.MomentVector(10, false, false);

        for(int i = 0 ; i < 11 ; i++){

            AddMouvV2 *mouv1 = new AddMouvV2(i,recList1[i],true);
            AddMouvV2 *mouv2 = new AddMouvV2(i,recList2[i],false);

            if(ui->walk->isChecked()){

                if(isAdded = mouv1->Walk(featuresMEI,featuresMHI,FN,isNormalized))
                    mouv2->Walk(featuresMEI,featuresMHI,FN,isNormalized);

                choice = 0;

                goto end;

            }

            if(ui->jump->isChecked()){

                if(isAdded = mouv1->Jump(featuresMEI,featuresMHI,FN,isNormalized))
                    mouv2->Jump(featuresMEI,featuresMHI,FN,isNormalized);

                choice = 1;

                goto end;

            }

            if(ui->run->isChecked()){

                if(isAdded = mouv1->Run(featuresMEI,featuresMHI,FN,isNormalized))
                    mouv2->Run(featuresMEI,featuresMHI,FN,isNormalized);

                choice = 2;

                goto end;

            }

            if(ui->side->isChecked()){

                if(isAdded = mouv1->Side(featuresMEI,featuresMHI,FN,isNormalized))
                    mouv2->Side(featuresMEI,featuresMHI,FN,isNormalized);

                choice = 3;

                goto end;

            }

            if(ui->skip->isChecked()){

                if(isAdded = mouv1->Skip(featuresMEI,featuresMHI,FN,isNormalized))
                    mouv2->Skip(featuresMEI,featuresMHI,FN,isNormalized);

                choice = 4;

                goto end;

            }

            if(ui->bend->isChecked()){

                if(isAdded = mouv1->Bend(featuresMEI,featuresMHI,FN,isNormalized))
                    mouv2->Bend(featuresMEI,featuresMHI,FN,isNormalized);

                choice = 5;

                goto end;

            }

            if(ui->jack->isChecked()){

                if(isAdded = mouv1->Jack(featuresMEI,featuresMHI,FN,isNormalized))
                    mouv2->Jack(featuresMEI,featuresMHI,FN,isNormalized);

                choice = 6;

                goto end;

            }

            if(ui->pjump->isChecked()){

                if(isAdded = mouv1->Pjump(featuresMEI,featuresMHI,FN,isNormalized))
                    mouv2->Pjump(featuresMEI,featuresMHI,FN,isNormalized);

                choice = 7;

                goto end;

            }

            if(ui->wave1->isChecked()){

                if(isAdded = mouv1->Wave1(featuresMEI,featuresMHI,FN,isNormalized))
                    mouv2->Wave1(featuresMEI,featuresMHI,FN,isNormalized);

                choice = 8;

                goto end;

            }

            if(ui->wave2->isChecked()){

                if(isAdded = mouv1->Wave2(featuresMEI,featuresMHI,FN,isNormalized))
                    mouv2->Wave2(featuresMEI,featuresMHI,FN,isNormalized);

                choice = 9;

                goto end;

            }

            end:
            delete(mouv1);
            delete(mouv2);


        }

    }


    if(isAdded){

        switch(choice){

        case 0:
            imgMEI->saveImage(this->BaseName.toStdString()+"/MEI_MHI/Walk/"+FN.toStdString()+"_MEI.png");
            imgMHI->saveImage(this->BaseName.toStdString()+"/MEI_MHI/Walk/"+FN.toStdString()+"_MHI.png");
            break;
        case 1:
            imgMEI->saveImage(this->BaseName.toStdString()+"/MEI_MHI/Jump/"+FN.toStdString()+"_MEI.png");
            imgMHI->saveImage(this->BaseName.toStdString()+"/MEI_MHI/Jump/"+FN.toStdString()+"_MHI.png");
            break;
        case 2:
            imgMEI->saveImage(this->BaseName.toStdString()+"/MEI_MHI/Run/"+FN.toStdString()+"_MEI.png");
            imgMHI->saveImage(this->BaseName.toStdString()+"/MEI_MHI/Run/"+FN.toStdString()+"_MHI.png");
            break;
        case 3:
            imgMEI->saveImage(this->BaseName.toStdString()+"/MEI_MHI/Side/"+FN.toStdString()+"_MEI.png");
            imgMHI->saveImage(this->BaseName.toStdString()+"/MEI_MHI/Side/"+FN.toStdString()+"_MHI.png");
            break;
        case 4:
            imgMEI->saveImage(this->BaseName.toStdString()+"/MEI_MHI/Skip/"+FN.toStdString()+"_MEI.png");
            imgMHI->saveImage(this->BaseName.toStdString()+"/MEI_MHI/Skip/"+FN.toStdString()+"_MHI.png");
            break;
        case 5:
            imgMEI->saveImage(this->BaseName.toStdString()+"/MEI_MHI/Bend/"+FN.toStdString()+"_MEI.png");
            imgMHI->saveImage(this->BaseName.toStdString()+"/MEI_MHI/Bend/"+FN.toStdString()+"_MHI.png");
            break;
        case 6:
            imgMEI->saveImage(this->BaseName.toStdString()+"/MEI_MHI/Jack/"+FN.toStdString()+"_MEI.png");
            imgMHI->saveImage(this->BaseName.toStdString()+"/MEI_MHI/Jack/"+FN.toStdString()+"_MHI.png");
            break;
        case 7:
            imgMEI->saveImage(this->BaseName.toStdString()+"/MEI_MHI/Pjump/"+FN.toStdString()+"_MEI.png");
            imgMHI->saveImage(this->BaseName.toStdString()+"/MEI_MHI/Pjump/"+FN.toStdString()+"_MHI.png");
            break;
        case 8:
            imgMEI->saveImage(this->BaseName.toStdString()+"/MEI_MHI/Wave1/"+FN.toStdString()+"_MEI.png");
            imgMHI->saveImage(this->BaseName.toStdString()+"/MEI_MHI/Wave1/"+FN.toStdString()+"_MHI.png");
            break;
        case 9:
            imgMEI->saveImage(this->BaseName.toStdString()+"/MEI_MHI/Wave2/"+FN.toStdString()+"_MEI.png");
            imgMHI->saveImage(this->BaseName.toStdString()+"/MEI_MHI/Wave2/"+FN.toStdString()+"_MHI.png");
            break;

        }

        delete(imgMEI);
        delete(imgMHI);

    }

    showBase();

    msgBox1->close();

    if(dialogsON && !isAdded)
        QMessageBox::critical(nullptr,tr("Error"),tr("Video Exist Deja"));

}

void newRecognizeUI::on_recon_clicked()
{

    if(!isVideoLoaded){
        QMessageBox::critical(
            this,
            tr("Error"),
            tr("Svp Charger une Video"));
        return;
    }

    if(!ui->isMEI->isChecked() && !ui->isMHI->isChecked()){
        QMessageBox::critical(
            this,
            tr("Error"),
            tr("Please Select at Least One (Include MEI , Include MHI)"));
        return;
    }

    QString filename = videoFilename;
    std::string cvt = filename.toStdString();

    if(!cvt.empty()){

        QMessageBox *msgBox1 = new QMessageBox;
        msgBox1->setText("In Progress.. Please Wait.");
        msgBox1->setWindowTitle("In Progress.. Please Wait.");
        msgBox1->setAttribute(Qt::WA_DeleteOnClose);
        msgBox1->setWindowModality(Qt::ApplicationModal);
        QCoreApplication::processEvents();
        msgBox1->show();
        QCoreApplication::processEvents();

        VideoAnalysis video(cvt);
        cv::Mat MEI,MHI;

        std::vector<double> featuresMEI, featuresMHI;

        int Order;
        bool TheMethode;

        if(video.isMoving(false)){

            if(this->BaseName.compare("Avec_Boite") == 0){
                MEI = video.centredMEI(setNoplace->framesMEI).clone();
                MHI = video.centredMHI(255,setNoplace->Var,setNoplace->framesMHI).clone();
            }else{
                MEI = video.GenerateMEI(setNoplace->framesMEI).clone();
                MHI = video.GenerateMHI(setNoplace->framesMHI,255,setNoplace->Var).clone();
            }

           ImageAnalysis imgMEI(MEI);
           ImageAnalysis imgMHI(MHI);

           featuresMEI = imgMEI.MomentVector(setNoplace->Ord, setNoplace->isMethode1, isNormalized);
           featuresMHI = imgMHI.MomentVector(setNoplace->Ord, setNoplace->isMethode1, isNormalized);

           Recognize **recList;

           if(setNoplace->isMethode1){
               recList = recList1;
           }else{
               recList = recList2;
           }

           Recognize *rec = recList[setNoplace->Ord];

           Classifier cls(rec->fileName,featuresMEI,featuresMHI);
           cls.GetAllFeatures();

           Order = setNoplace->Ord;
           TheMethode = setNoplace->isMethode1;

           if(setNoplace->isMEI && setNoplace->isMHI){

                int **Matrix;
                QString Mvt;

                if(setNoplace->isprioMEI){

                    Matrix = cls.MatrixNoPlace_MEI();
                    Mvt = rec->FinalChoosing(Matrix,cls,true,true);

                }else{

                    Matrix = cls.MatrixNoPlace_MHI();
                    Mvt = rec->FinalChoosingNEW(Matrix,cls,true,true);

                }

                ui->preC->setText(rec->PreClassification);
                ui->mvtname->setText(Mvt.toUtf8());

           }else if(setNoplace->isMEI){

               int **Matrix = cls.MatrixNoPlace_MEI();
               QString Mvt = rec->FinalChoosing(Matrix,cls,false,true);
               ui->mvtname->setText(Mvt.toUtf8());

           }else{

               int **Matrix = cls.MatrixNoPlace_MHI();
               QString Mvt = rec->FinalChoosing(Matrix,cls,false,true);
               ui->mvtname->setText(Mvt.toUtf8());
           }

        }else{
           MEI = video.GenerateMEI(setInplace->framesMEI);
           MHI = video.GenerateMHI(setInplace->framesMHI,255,setInplace->Var);

           ImageAnalysis imgMEI(MEI);
           ImageAnalysis imgMHI(MHI);

           featuresMEI = imgMEI.MomentVector(setInplace->Ord, setInplace->isMethode1, isNormalized);
           featuresMHI = imgMHI.MomentVector(setInplace->Ord, setInplace->isMethode1, isNormalized);

           Recognize **recList;

           if(setInplace->isMethode1){
               recList = recList1;
           }else{
               recList = recList2;
           }

           Recognize *rec = recList[setInplace->Ord];

           Classifier cls(rec->fileName,featuresMEI,featuresMHI);
           cls.GetAllFeatures();

           Order = setInplace->Ord;
           TheMethode = setInplace->isMethode1;

           if(setInplace->isMEI && setInplace->isMHI){

               int **Matrix;
               QString Mvt;

               if(setInplace->isprioMEI){

                   Matrix = cls.MatrixInPlace_MEI();
                   Mvt = rec->FinalChoosing(Matrix,cls,true,false);

               }else{

                   Matrix = cls.MatrixInPlace_MHI();
                   Mvt = rec->FinalChoosingNEW(Matrix,cls,true,false);

               }

               ui->preC->setText(rec->PreClassification);
               ui->mvtname->setText(Mvt.toUtf8());

           }else if(setInplace->isMEI){

               int **Matrix = cls.MatrixInPlace_MEI();
               QString Mvt = rec->FinalChoosing(Matrix,cls,false,false);
               ui->mvtname->setText(Mvt.toUtf8());

           }else{

               int **Matrix = cls.MatrixInPlace_MHI();
               QString Mvt = rec->FinalChoosing(Matrix,cls,false,false);
               ui->mvtname->setText(Mvt.toUtf8());

           }
        }

        QFile file1("tempMEIMHI");

        file1.remove();

        file1.open(QIODevice::ReadWrite);

        QString toWrite = "tempMEIMHI";

        for(int i = 0 ; i < featuresMEI.size() ; i++){

            toWrite += ":" + QString::number(featuresMEI[i], 'g', 64);

        }

        toWrite += "\ntempMEIMHI";

        for(int i = 0 ; i < featuresMHI.size() ; i++){

            toWrite += ":" + QString::number(featuresMHI[i], 'g', 64);

        }

        file1.write(toWrite.toUtf8());

        file1.close();

        QString tempCurrentfile = currentFile;

        currentFile = "tempMEIMHI";

        ShowTable("tempMEIMHI",ui->tableWidget_2,Order ,TheMethode);

        currentFile = tempCurrentfile;

        msgBox1->close();

    }


}

void newRecognizeUI::on_crsVali_clicked()
{

    if(!ui->isMEI->isChecked() && !ui->isMHI->isChecked()){
        QMessageBox::critical(
            this,
            tr("Error"),
            tr("Please Select at Least One (Include MEI , Include MHI)"));
        return;
    }

    QMessageBox *msgBox1 = new QMessageBox;
    msgBox1->setText("In Progress.. Please Wait.");
    msgBox1->setWindowTitle("In Progress.. Please Wait.");
    msgBox1->setAttribute(Qt::WA_DeleteOnClose);
    msgBox1->setWindowModality(Qt::ApplicationModal);
    QCoreApplication::processEvents();
    msgBox1->show();
    QCoreApplication::processEvents();

    Recognize *recInplace;
    Recognize *recNoplace;

    if(setInplace->isMethode1){
        recInplace = recList1[setInplace->Ord];
    }else{
        recInplace = recList2[setInplace->Ord];
    }

    if(setNoplace->isMethode1){
        recNoplace = recList1[setNoplace->Ord];
    }else{
        recNoplace = recList2[setNoplace->Ord];
    }

    CrossValidation *CR = new CrossValidation(recInplace->fileName, recNoplace->fileName, setInplace, setNoplace);

    ui->tauplace->clear();
    ui->tauplace_2->clear();

    ui->tauplace->setText( (QString::number(CR->PerformePlaceTest()*100) + "%").toUtf8() );

    if(setInplace->isMEI && setInplace->isMHI)
        ui->tauplace_2->setText( (QString::number((CR->preTaux1/5)*100) + "%").toUtf8() );

    //CR->TauxPreClassMEI();

    msgBox1->close();

    delete(CR);

}

void newRecognizeUI::on_crsVali_2_clicked()
{

    if(!ui->isMEI->isChecked() && !ui->isMHI->isChecked()){
        QMessageBox::critical(
            this,
            tr("Error"),
            tr("Please Select at Least One (Include MEI , Include MHI)"));
        return;
    }

    QMessageBox *msgBox1 = new QMessageBox;
    msgBox1->setText("In Progress.. Please Wait.");
    msgBox1->setWindowTitle("In Progress.. Please Wait.");
    msgBox1->setAttribute(Qt::WA_DeleteOnClose);
    msgBox1->setWindowModality(Qt::ApplicationModal);
    QCoreApplication::processEvents();
    msgBox1->show();
    QCoreApplication::processEvents();

    Recognize *recInplace;
    Recognize *recNoplace;

    if(setInplace->isMethode1){
        recInplace = recList1[setInplace->Ord];
    }else{
        recInplace = recList2[setInplace->Ord];
    }

    if(setNoplace->isMethode1){
        recNoplace = recList1[setNoplace->Ord];
    }else{
        recNoplace = recList2[setNoplace->Ord];
    }

    CrossValidation *CR = new CrossValidation(recInplace->fileName, recNoplace->fileName, setInplace, setNoplace);

    ui->taunoplace->clear();
    ui->taunoplace_2->clear();

    ui->taunoplace->setText( (QString::number(CR->PerformeNoPlaceTest()*100) + "%").toUtf8() );

    if(setNoplace->isMEI && setNoplace->isMHI)
        ui->taunoplace_2->setText( (QString::number((CR->preTaux2/5)*100) + "%").toUtf8() );

    msgBox1->close();

    delete(CR);

}

void newRecognizeUI::on_crsVali_5_clicked()
{

    if(!ui->isMEI->isChecked() && !ui->isMHI->isChecked()){
        QMessageBox::critical(
            this,
            tr("Error"),
            tr("Please Select at Least One (Include MEI , Include MHI)"));
        return;
    }

    QMessageBox *msgBox1 = new QMessageBox;
    msgBox1->setText("In Progress.. Please Wait.");
    msgBox1->setWindowTitle("In Progress.. Please Wait.");
    msgBox1->setAttribute(Qt::WA_DeleteOnClose);
    msgBox1->setWindowModality(Qt::ApplicationModal);
    QCoreApplication::processEvents();
    msgBox1->show();
    QCoreApplication::processEvents();

    Recognize *recInplace;
    Recognize *recNoplace;

    if(setInplace->isMethode1){
        recInplace = recList1[setInplace->Ord];
    }else{
        recInplace = recList2[setInplace->Ord];
    }

    if(setNoplace->isMethode1){
        recNoplace = recList1[setNoplace->Ord];
    }else{
        recNoplace = recList2[setNoplace->Ord];
    }

    CrossValidation *CR = new CrossValidation(recInplace->fileName, recNoplace->fileName, setInplace, setNoplace);

    ui->tau->setText( (QString::number(CR->PerformeAllTest()*100) + "%").toUtf8() );

    msgBox1->close();

    delete(CR);

}

void newRecognizeUI::on_multAdd_clicked()
{

    QStringList filenames = QFileDialog::getOpenFileNames(this,tr("AVI files"),QDir::currentPath(),tr("AVI files (*.avi);;All files (*.*)") );
    if( !filenames.isEmpty() )
    {

        QMessageBox *msgBox1 = new QMessageBox;
        msgBox1->setText("In Progress.. Please Wait.");
        msgBox1->setWindowTitle("In Progress.. Please Wait.");
        msgBox1->setAttribute(Qt::WA_DeleteOnClose);
        msgBox1->setWindowModality(Qt::ApplicationModal);
        QCoreApplication::processEvents();
        msgBox1->show();
        QCoreApplication::processEvents();

        QString tempVid = videoFilename;

        dialogsON = false;

        for (int i =0;i<filenames.count();i++){

            videoFilename = filenames.at(i);
            on_addV_clicked();

        }

        videoFilename = tempVid;

        dialogsON = true;

        msgBox1->close();

    }

}

void newRecognizeUI::on_exit_clicked()
{

    this->close();

}


void newRecognizeUI::closeEvent(QCloseEvent *event){

    this->parentWidget()->close();
    mainWin->hide();
    mainWin->show();
    mainWin->showMinimized();
    mainWin->showMaximized();
    event->accept();

}

void newRecognizeUI::on_Suppr_clicked()
{

    if(ui->listWidget->currentItem() == nullptr){
        QMessageBox::critical(
            this,
            tr("Error"),
            tr("Base Empty or you didn't select anything"));
        return;
    }

    QString tempvideoFilename = ui->listWidget->currentItem()->text();

    QMessageBox *msgBox1 = new QMessageBox;
    msgBox1->setText("In Progress.. Please Wait.");
    msgBox1->setWindowTitle("In Progress.. Please Wait.");
    msgBox1->setAttribute(Qt::WA_DeleteOnClose);
    msgBox1->setWindowModality(Qt::ApplicationModal);
    QCoreApplication::processEvents();
    msgBox1->show();
    QCoreApplication::processEvents();

    for(int i = 0 ; i < 11 ; i++){

        if(ui->walk->isChecked()){

            recList1[i]->Supprimer(recList1[i]->fileName+"/NOPLACE/Walk", tempvideoFilename);
            recList2[i]->Supprimer(recList2[i]->fileName+"/NOPLACE/Walk", tempvideoFilename);
            goto end;

        }

        if(ui->jump->isChecked()){

            recList1[i]->Supprimer(recList1[i]->fileName+"/NOPLACE/Jump", tempvideoFilename);
            recList2[i]->Supprimer(recList2[i]->fileName+"/NOPLACE/Jump", tempvideoFilename);
            goto end;

        }

        if(ui->run->isChecked()){

            recList1[i]->Supprimer(recList1[i]->fileName+"/NOPLACE/Run", tempvideoFilename);
            recList2[i]->Supprimer(recList2[i]->fileName+"/NOPLACE/Run", tempvideoFilename);
            goto end;

        }

        if(ui->side->isChecked()){

            recList1[i]->Supprimer(recList1[i]->fileName+"/NOPLACE/Side", tempvideoFilename);
            recList2[i]->Supprimer(recList2[i]->fileName+"/NOPLACE/Side", tempvideoFilename);
            goto end;

        }

        if(ui->skip->isChecked()){

            recList1[i]->Supprimer(recList1[i]->fileName+"/NOPLACE/Skip", tempvideoFilename);
            recList2[i]->Supprimer(recList2[i]->fileName+"/NOPLACE/Skip", tempvideoFilename);

            goto end;

        }

        if(ui->bend->isChecked()){

            recList1[i]->Supprimer(recList1[i]->fileName+"/INPLACE/Bend", tempvideoFilename);
            recList2[i]->Supprimer(recList2[i]->fileName+"/INPLACE/Bend", tempvideoFilename);
            goto end;

        }

        if(ui->jack->isChecked()){

            recList1[i]->Supprimer(recList1[i]->fileName+"/INPLACE/Jack", tempvideoFilename);
            recList2[i]->Supprimer(recList2[i]->fileName+"/INPLACE/Jack", tempvideoFilename);
            goto end;

        }

        if(ui->pjump->isChecked()){

            recList1[i]->Supprimer(recList1[i]->fileName+"/INPLACE/Pjump", tempvideoFilename);
            recList2[i]->Supprimer(recList2[i]->fileName+"/INPLACE/Pjump", tempvideoFilename);
            goto end;

        }

        if(ui->wave1->isChecked()){

            recList1[i]->Supprimer(recList1[i]->fileName+"/INPLACE/Wave1", tempvideoFilename);
            recList2[i]->Supprimer(recList2[i]->fileName+"/INPLACE/Wave1", tempvideoFilename);
            goto end;

        }

        if(ui->wave2->isChecked()){

            recList1[i]->Supprimer(recList1[i]->fileName+"/INPLACE/Wave2", tempvideoFilename);
            recList2[i]->Supprimer(recList2[i]->fileName+"/INPLACE/Wave2", tempvideoFilename);
            goto end;

        }

        end:
        continue;

    }

    showBase();

    ui->MEIviewer2->clear();
    ui->MHIviewer2->clear();

    ui->tau->clear();
    ui->taunoplace->clear();
    ui->tauplace->clear();
    ui->mvtname->clear();
    ui->preC->clear();
    ui->taunoplace_2->clear();
    ui->tauplace_2->clear();

    msgBox1->close();


}

void newRecognizeUI::on_walk_clicked()
{

    currentFile = this->BaseName+"/Methode2/Order10/NOPLACE/Walk";
    showBase();

}

void newRecognizeUI::on_run_clicked()
{

    currentFile = this->BaseName+"/Methode2/Order10/NOPLACE/Run";
    showBase();

}

void newRecognizeUI::on_skip_clicked()
{

    currentFile = this->BaseName+"/Methode2/Order10/NOPLACE/Skip";
    showBase();

}

void newRecognizeUI::on_jump_clicked()
{

    currentFile = this->BaseName+"/Methode2/Order10/NOPLACE/Jump";
    showBase();

}

void newRecognizeUI::on_side_clicked()
{

    currentFile = this->BaseName+"/Methode2/Order10/NOPLACE/Side";
    showBase();

}

void newRecognizeUI::on_bend_clicked()
{

    currentFile = this->BaseName+"/Methode2/Order10/INPLACE/Bend";
    showBase();

}

void newRecognizeUI::on_pjump_clicked()
{

    currentFile = this->BaseName+"/Methode2/Order10/INPLACE/Pjump";
    showBase();

}

void newRecognizeUI::on_jack_clicked()
{

    currentFile = this->BaseName+"/Methode2/Order10/INPLACE/Jack";
    showBase();

}

void newRecognizeUI::on_wave1_clicked()
{

    currentFile = this->BaseName+"/Methode2/Order10/INPLACE/Wave1";
    showBase();

}

void newRecognizeUI::on_wave2_clicked()
{

    currentFile = this->BaseName+"/Methode2/Order10/INPLACE/Wave2";
    showBase();

}

void newRecognizeUI::on_listWidget_itemSelectionChanged()
{

    ShowTable(ui->listWidget->currentItem()->text(),ui->tableWidget,10,false);

    QPixmap pix1(this->BaseName+"/MEI_MHI/"+currentFile.split("/").last()+"/"+ui->listWidget->currentItem()->text() + "_MEI.png");
    ui->MEIviewer2->setPixmap(pix1);
    ui->MEIviewer2->setScaledContents( true );
    ui->MEIviewer2 ->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    QPixmap pix2(this->BaseName+"/MEI_MHI/"+currentFile.split("/").last()+"/"+ui->listWidget->currentItem()->text() + "_MHI.png");
    ui->MHIviewer2->setPixmap(pix2);
    ui->MHIviewer2->setScaledContents( true );
    ui->MHIviewer2 ->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

}

void newRecognizeUI::on_tabWidget_tabBarClicked(int index)
{

    QString parame = "- Les Parametre Utiliser Pour les Mouvement Avec Deplacement : \n";

    if(setNoplace->isMethode1){
        parame += "\nla Methode de Reconnaissance : Methode 1\n";
    }else{
        parame += "\nla Methode de Reconnaissance : Methode 2\n";
    }

    parame += "\nOrdre des moments : "+QString::number(setNoplace->Ord)+"\n";

    if(setNoplace->isMEI){
        parame += "\nInclusion de MEI : OUI\n";
    }else{
        parame += "\nInclusion de MEI : NON\n";
    }

    if(setNoplace->isMHI){
        parame += "\nInclusion de MHI : OUI\n";
    }else{
        parame += "\nInclusion de MHI : NON\n";
    }

    if(setNoplace->isMEI && setNoplace->isMHI && setNoplace->isprioMEI){

        parame += "\nPre-Classification Avec MEI\n";

    }else if(setNoplace->isMEI && setNoplace->isMHI && !setNoplace->isprioMEI){

        parame += "\nPre-Classification Avec MHI\n";

    }

    QString parame2 = "\n- Les Parametre Utiliser Pour les Mouvement Sans Deplacement : \n";

    if(setInplace->isMethode1){
        parame2 += "\nla Methode de Reconnaissance : Methode 1\n";
    }else{
        parame2 += "\nla Methode de Reconnaissance : Methode 2\n";
    }

    parame2 += "\nOrdre des moments : "+QString::number(setInplace->Ord)+"\n";

    if(setInplace->isMEI){
        parame2 += "\nInclusion de MEI : OUI\n";
    }else{
        parame2 += "\nInclusion de MEI : NON\n";
    }

    if(setInplace->isMHI){
        parame2 += "\nInclusion de MHI : OUI\n";
    }else{
        parame2 += "\nInclusion de MHI : NON\n";
    }

    if(setInplace->isMEI && setInplace->isMHI && setInplace->isprioMEI){

        parame2 += "\nPre-Classification Avec MEI\n";

    }else if(setInplace->isMEI && setInplace->isMHI && !setInplace->isprioMEI){

        parame2 += "\nPre-Classification Avec MHI\n";

    }

    ui->usedParams->setText(parame);
    ui->usedParams_2->setText(parame2);

}

void newRecognizeUI::checkIFSomethingChanged(int newOrder){


    if(prevSetInPlace->Ord == newOrder && ui->isMEI->isChecked() == prevSetInPlace->isMEI && prevSetInPlace->isMHI == ui->isMHI->isChecked() && ui->Meth1->isChecked() == prevSetInPlace->isMethode1 && prevSetInPlace->isprioMEI == ui->prioMEI_2->isChecked()){
        ui->sauvParams->setEnabled(false);
        ui->warningM->setVisible(false);
        return;
    }

    ui->warningM->setVisible(true);
    ui->sauvParams->setEnabled(true);

}

void newRecognizeUI::on_ord0_clicked()
{

    checkIFSomethingChanged(0);
    currentInPlaceOrder = 0;

}

void newRecognizeUI::on_ord1_clicked()
{

    checkIFSomethingChanged(1);
    currentInPlaceOrder = 1;

}

void newRecognizeUI::on_ord2_clicked()
{

    checkIFSomethingChanged(2);
    currentInPlaceOrder = 2;

}

void newRecognizeUI::on_ord3_clicked()
{

    checkIFSomethingChanged(3);
    currentInPlaceOrder = 3;

}

void newRecognizeUI::on_ord4_clicked()
{

    checkIFSomethingChanged(4);
    currentInPlaceOrder = 4;

}

void newRecognizeUI::on_ord5_clicked()
{

    checkIFSomethingChanged(5);
    currentInPlaceOrder = 5;

}

void newRecognizeUI::on_ord6_clicked()
{

    checkIFSomethingChanged(6);
    currentInPlaceOrder = 6;

}

void newRecognizeUI::on_ord7_clicked()
{

    checkIFSomethingChanged(7);
    currentInPlaceOrder = 7;

}

void newRecognizeUI::on_ord8_clicked()
{

    checkIFSomethingChanged(8);
    currentInPlaceOrder = 8;

}

void newRecognizeUI::on_ord9_clicked()
{

    checkIFSomethingChanged(9);
    currentInPlaceOrder = 9;

}

void newRecognizeUI::on_ord10_clicked()
{

    checkIFSomethingChanged(10);
    currentInPlaceOrder = 10;

}

void newRecognizeUI::on_isMEI_clicked()
{

    checkIFSomethingChanged(currentInPlaceOrder);

    if(ui->isMEI->isChecked() == false || ui->isMHI->isChecked() == false){
        ui->prioMEI_2->setDisabled(true);
        ui->prioMHI_2->setDisabled(true);
    }else{
        ui->prioMEI_2->setDisabled(false);
        ui->prioMHI_2->setDisabled(false);
    }
}

void newRecognizeUI::on_isMHI_clicked()
{

    checkIFSomethingChanged(currentInPlaceOrder);

    if(ui->isMEI->isChecked() == false || ui->isMHI->isChecked() == false){
        ui->prioMEI_2->setDisabled(true);
        ui->prioMHI_2->setDisabled(true);
    }else{
        ui->prioMEI_2->setDisabled(false);
        ui->prioMHI_2->setDisabled(false);
    }


}

void newRecognizeUI::on_Meth1_clicked()
{

    checkIFSomethingChanged(currentInPlaceOrder);

}

void newRecognizeUI::on_Meth2_clicked()
{

    checkIFSomethingChanged(currentInPlaceOrder);

}

void newRecognizeUI::on_sauvParams_clicked()
{

    if(ui->isMEI->isChecked() == false && ui->isMHI->isChecked() == false){
        QMessageBox::critical(
            this,
            tr("Error"),
            tr("Selectionner un des deux :\n-Inclusion MEI\n-Inclusion MHI"));
        return;
    }

    LoadSettingsInPlace();

    delete(prevSetInPlace);
    prevSetInPlace = new Settings(setInplace->framesMEI, setInplace->framesMHI, setInplace->Var, setInplace->Ord, setInplace->isMethode1, setInplace->isMEI , setInplace->isMHI, setInplace->isprioMEI);

    ui->sauvParams->setEnabled(false);
    ui->warningM->setVisible(false);
    ui->tauplace->clear();
    ui->tau->clear();
    ui->tauplace_2->clear();

    ui->tableWidget_2->clear();

    ui->tableWidget_2->setHorizontalHeaderItem(0, new QTableWidgetItem("P"));
    ui->tableWidget_2->setHorizontalHeaderItem(1, new QTableWidgetItem("Q"));
    ui->tableWidget_2->setHorizontalHeaderItem(2, new QTableWidgetItem("MEI"));
    ui->tableWidget_2->setHorizontalHeaderItem(3, new QTableWidgetItem("MHI"));

    ui->mvtname->clear();
    ui->preC->clear();

}


void newRecognizeUI::checkIFSomethingChangedNoPlace(int newOrder){


    if(prevSetNoPlace->Ord == newOrder && ui->isMEI_2->isChecked() == prevSetNoPlace->isMEI && prevSetNoPlace->isMHI == ui->isMHI_2->isChecked() && ui->Meth1_2->isChecked() == prevSetNoPlace->isMethode1 && prevSetNoPlace->isprioMEI == ui->prioMEI->isChecked()){
        ui->sauvParams_2->setEnabled(false);
        ui->warningM_2->setVisible(false);
        return;
    }

    ui->warningM_2->setVisible(true);
    ui->sauvParams_2->setEnabled(true);

}


void newRecognizeUI::on_ord0_2_clicked()
{

    checkIFSomethingChangedNoPlace(0);
    currentNoPlaceOrder = 0;

}

void newRecognizeUI::on_ord1_2_clicked()
{

    checkIFSomethingChangedNoPlace(1);
    currentNoPlaceOrder = 1;

}

void newRecognizeUI::on_ord2_2_clicked()
{

    checkIFSomethingChangedNoPlace(2);
    currentNoPlaceOrder = 2;

}



void newRecognizeUI::on_ord3_2_clicked()
{

    checkIFSomethingChangedNoPlace(3);
    currentNoPlaceOrder = 3;

}

void newRecognizeUI::on_ord4_2_clicked()
{

    checkIFSomethingChangedNoPlace(4);
    currentNoPlaceOrder = 4;

}

void newRecognizeUI::on_ord5_2_clicked()
{

    checkIFSomethingChangedNoPlace(5);
    currentNoPlaceOrder = 5;

}

void newRecognizeUI::on_ord6_2_clicked()
{

    checkIFSomethingChangedNoPlace(6);
    currentNoPlaceOrder = 6;

}

void newRecognizeUI::on_ord7_2_clicked()
{

    checkIFSomethingChangedNoPlace(7);
    currentNoPlaceOrder = 7;

}

void newRecognizeUI::on_ord8_2_clicked()
{

    checkIFSomethingChangedNoPlace(8);
    currentNoPlaceOrder = 8;

}

void newRecognizeUI::on_ord9_2_clicked()
{

    checkIFSomethingChangedNoPlace(9);
    currentNoPlaceOrder = 9;

}

void newRecognizeUI::on_ord10_2_clicked()
{

    checkIFSomethingChangedNoPlace(10);
    currentNoPlaceOrder = 10;

}

void newRecognizeUI::on_isMEI_2_clicked()
{

    checkIFSomethingChangedNoPlace(currentNoPlaceOrder);

    if(ui->isMEI_2->isChecked() == false || ui->isMHI_2->isChecked() == false){
        ui->prioMEI->setDisabled(true);
        ui->prioMHI->setDisabled(true);
    }else{
        ui->prioMEI->setDisabled(false);
        ui->prioMHI->setDisabled(false);
    }


}



void newRecognizeUI::on_isMHI_2_clicked()
{

    checkIFSomethingChangedNoPlace(currentNoPlaceOrder);

    if(ui->isMEI_2->isChecked() == false || ui->isMHI_2->isChecked() == false){
        ui->prioMEI->setDisabled(true);
        ui->prioMHI->setDisabled(true);
    }else{
        ui->prioMEI->setDisabled(false);
        ui->prioMHI->setDisabled(false);
    }


}

void newRecognizeUI::on_Meth1_2_clicked()
{

    checkIFSomethingChangedNoPlace(currentNoPlaceOrder);

}

void newRecognizeUI::on_Meth2_2_clicked()
{

    checkIFSomethingChangedNoPlace(currentNoPlaceOrder);

}

void newRecognizeUI::on_sauvParams_2_clicked()
{

    if(ui->isMEI_2->isChecked() == false && ui->isMHI_2->isChecked() == false){
        QMessageBox::critical(
            this,
            tr("Error"),
            tr("Selectionner un des deux :\n-Inclusion MEI\n-Inclusion MHI"));
        return;
    }

    ui->sauvParams_2->setEnabled(false);
    ui->warningM_2->setVisible(false);

    ui->taunoplace->clear();
    ui->tau->clear();
    ui->tableWidget_2->clear();
    ui->taunoplace_2->clear();

    ui->tableWidget_2->setHorizontalHeaderItem(0, new QTableWidgetItem("P"));
    ui->tableWidget_2->setHorizontalHeaderItem(1, new QTableWidgetItem("Q"));
    ui->tableWidget_2->setHorizontalHeaderItem(2, new QTableWidgetItem("MEI"));
    ui->tableWidget_2->setHorizontalHeaderItem(3, new QTableWidgetItem("MHI"));

    ui->mvtname->clear();
    ui->preC->clear();

    LoadSettingsNoPlace();

    delete(prevSetNoPlace);
    prevSetNoPlace = new Settings(setNoplace->framesMEI, setNoplace->framesMHI, setNoplace->Var, setNoplace->Ord, setNoplace->isMethode1, setNoplace->isMEI , setNoplace->isMHI, setNoplace->isprioMEI);


}


void newRecognizeUI::on_prioMEI_clicked()
{

    checkIFSomethingChangedNoPlace(currentNoPlaceOrder);

}

void newRecognizeUI::on_prioMHI_clicked()
{

    checkIFSomethingChangedNoPlace(currentNoPlaceOrder);

}

void newRecognizeUI::on_prioMEI_2_clicked()
{

    checkIFSomethingChanged(currentInPlaceOrder);

}

void newRecognizeUI::on_prioMHI_2_clicked()
{

    checkIFSomethingChanged(currentInPlaceOrder);

}
