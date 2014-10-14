#ifndef RECIEVEPROGRESSDIALOG_H
#define RECIEVEPROGRESSDIALOG_H

#include <QDialog>

namespace Ui {
class ReceiveProgressDialog;
}

class ReceiveProgressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReceiveProgressDialog(QWidget *parent = 0);
    ~ReceiveProgressDialog();

public slots:
    void Progress(int r, int t);

private slots:
    void on_pushButtonCancel_clicked();

private:
    Ui::ReceiveProgressDialog *ui;
};

#endif // RECIEVEPROGRESSDIALOG_H
