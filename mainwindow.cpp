#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newrecognizeui.h"
#include "modechooser.h"

/*
 * Class de la fenetre Principale
 * */

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix2("USTHB_logo.png");
    ui->logo->setPixmap(pix2);
    ui->logo->setScaledContents( true );
    ui->logo ->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    ui->logo_2->setPixmap(pix2);
    ui->logo_2->setScaledContents( true );
    ui->logo_2 ->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    //this->setAttribute(Qt::WA_DeleteOnClose);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Reset_clicked()
{

    QMessageBox::StandardButton reply;
      reply = QMessageBox::question(this, "Are you Sure ?", "Cette Operation va supprimer tout les donnees de programme , Vous etes sure de faire cette Operation ?",
                                    QMessageBox::Yes|QMessageBox::No);

      if (reply == QMessageBox::Yes) {

          QDir dir1("Avec_Boite");
          dir1.removeRecursively();

          QDir dir2("Sans_Boite");
          dir2.removeRecursively();

          QFile file1("loadMEI.png");
          file1.remove();

          QFile file2("loadMHI.png");
          file2.remove();

          QFile file3("tempMEIMHI");
          file3.remove();

          QMessageBox::information(this,tr("Completed"),tr("Done"));
          
      }

}


void MainWindow::on_pushButton_2_clicked()
{

    this->close();

}

void MainWindow::on_recoMode_clicked()
{

    ModeChooser *choose = new ModeChooser(this);
    choose->setModal(true);
    choose->exec();

}
