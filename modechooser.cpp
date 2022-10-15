#include "modechooser.h"
#include "ui_modechooser.h"

ModeChooser::ModeChooser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModeChooser)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose);

}

ModeChooser::~ModeChooser()
{
    delete ui;
}

void ModeChooser::on_close_clicked()
{

    this->parentWidget()->show();
    this->close();

}

void ModeChooser::on_recWith_clicked()
{

    newRecognizeUI *reco = new newRecognizeUI(this);
    reco->Init("Avec_Boite",0,25,8,this->parentWidget());
    reco->show();

}



void ModeChooser::on_recWithout_clicked()
{

    newRecognizeUI *reco = new newRecognizeUI(this);
    reco->Init("Sans_Boite",30,45,8,this->parentWidget());
    reco->show();

}
