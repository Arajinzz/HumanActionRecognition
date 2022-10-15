#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*
 * Class de la fenetre Principale
 * */

#include <QMainWindow>
#include "videoanalysis.h"
#include "recognize.h"
#include "opencv2/opencv.hpp"
#include <QDebug>
#include "classifier.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Reset_clicked();

    void on_pushButton_2_clicked();

    void on_recoMode_clicked();

private:
    Ui::MainWindow *ui;

    Recognize *rec;
    bool isMethod1 = false;

};

#endif // MAINWINDOW_H
