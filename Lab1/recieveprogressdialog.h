#ifndef RECIEVEPROGRESSDIALOG_H
#define RECIEVEPROGRESSDIALOG_H
//прогресс скачивания
#include <QDialog>

namespace Ui {
class RecieveProgressDialog;
}

class RecieveProgressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RecieveProgressDialog(QWidget *parent = 0);
    ~RecieveProgressDialog();

private slots:
    void on_pushButtonCancel_clicked();

private:
    Ui::RecieveProgressDialog *ui;
};

#endif // RECIEVEPROGRESSDIALOG_H
