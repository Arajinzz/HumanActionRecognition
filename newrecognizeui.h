#ifndef NEWRECOGNIZEUI_H
#define NEWRECOGNIZEUI_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QFileDialog>
#include <QProgressBar>
#include <QSlider>
#include <QCloseEvent>
#include "videoanalysis.h"
#include "imageanalysis.h"
#include "opencv2/opencv.hpp"
#include "recognize.h"
#include "addmouvv2.h"
#include "settings.h"
#include "crossvalidation.h"
#include <QCloseEvent>
#include <QInputDialog>
#include <QTableWidget>
#include <QSettings>

namespace Ui {
class newRecognizeUI;
}

class newRecognizeUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit newRecognizeUI(QWidget *parent = 0);
    ~newRecognizeUI();

    void closeEvent(QCloseEvent *event);
    void Init(QString BaseName, int framesMEI, int framesMHI, int Var, QWidget *mainWin);
    void LoadSettingsInPlace();
    void LoadSettingsNoPlace();
    void ShowTable(QString toShow, QTableWidget *table, int order, bool isMethode1);
    void showBase();
    void checkIFSomethingChanged(int newOrder);
    void play();
    void checkIFSomethingChangedNoPlace(int newOrder);



private slots:
    void on_play_clicked();

    void on_stop_clicked();

    void on_loadVideo_clicked();

    void on_addV_clicked();

    void on_recon_clicked();

    void on_crsVali_clicked();

    void on_multAdd_clicked();

    void on_exit_clicked();

    void on_Suppr_clicked();

    void on_walk_clicked();

    void on_run_clicked();

    void on_skip_clicked();

    void on_jump_clicked();

    void on_side_clicked();

    void on_bend_clicked();

    void on_pjump_clicked();

    void on_jack_clicked();

    void on_wave1_clicked();

    void on_wave2_clicked();

    void on_listWidget_itemSelectionChanged();

    void on_tabWidget_tabBarClicked(int index);

    void on_ord0_clicked();

    void on_ord1_clicked();

    void on_ord2_clicked();

    void on_ord3_clicked();

    void on_ord4_clicked();

    void on_ord5_clicked();

    void on_ord6_clicked();

    void on_ord7_clicked();

    void on_ord8_clicked();

    void on_ord9_clicked();

    void on_ord10_clicked();

    void on_isMEI_clicked();

    void on_isMHI_clicked();

    void on_Meth1_clicked();

    void on_Meth2_clicked();

    void on_sauvParams_clicked();

    void on_ord0_2_clicked();

    void on_ord2_2_clicked();

    void on_ord1_2_clicked();

    void on_ord3_2_clicked();

    void on_ord4_2_clicked();

    void on_ord5_2_clicked();

    void on_ord6_2_clicked();

    void on_ord7_2_clicked();

    void on_ord8_2_clicked();

    void on_ord9_2_clicked();

    void on_ord10_2_clicked();

    void on_isMEI_2_clicked();

    void on_isMHI_2_clicked();

    void on_Meth1_2_clicked();

    void on_Meth2_2_clicked();

    void on_sauvParams_2_clicked();

    void on_crsVali_2_clicked();

    void on_crsVali_5_clicked();

    void on_prioMEI_clicked();

    void on_prioMHI_clicked();

    void on_prioMEI_2_clicked();

    void on_prioMHI_2_clicked();

private:
    Ui::newRecognizeUI *ui;

    QMediaPlayer *player;
    QSlider *slider;
    QVideoWidget *vw;

    QString videoFilename;
    QString currentFile;

    cv::Mat image;

    bool isVideoLoaded = false;
    bool isImageLoaded = false;
    bool dialogsON = true;

    Recognize *recList1[11];
    Recognize *recList2[11];

    Settings *setInplace = NULL;
    Settings *setNoplace = NULL;
    Settings *prevSetInPlace = NULL;
    Settings *prevSetNoPlace = NULL;

    int currentInPlaceOrder;
    int currentNoPlaceOrder;

    bool isInplaceSaved = false;
    bool isNoplaceSaved = false;

    int framesMEI, framesMHI, Var;

    QString BaseName;

    QWidget *mainWin;

    bool isNormalized = true;

};

#endif // NEWRECOGNIZEUI_H
