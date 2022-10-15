#ifndef MODECHOOSER_H
#define MODECHOOSER_H

#include <QDialog>
#include <newrecognizeui.h>

namespace Ui {
class ModeChooser;
}

class ModeChooser : public QDialog
{
    Q_OBJECT

public:
    explicit ModeChooser(QWidget *parent = 0);
    ~ModeChooser();

private slots:
    void on_close_clicked();

    void on_recWith_clicked();

    void on_recWithout_clicked();

private:
    Ui::ModeChooser *ui;
};

#endif // MODECHOOSER_H
