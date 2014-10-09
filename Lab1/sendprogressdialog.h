#ifndef SENDPROGRESSDIALOG_H
#define SENDPROGRESSDIALOG_H
//прогресс отправления файла
#include <QDialog>
#include <QString>

namespace Ui {
class SendProgressDialog;
}

class SendProgressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SendProgressDialog(QWidget *parent = 0);
  /*  QString ip;
    QString port;
    QString progr;*/
    ~SendProgressDialog();

private slots:
    void on_pushButtonCancel_clicked();

public slots:
    void RxDataFromSendDialog(QString DestIp, QString DestPort, QString DestFile);


signals:

private:
    Ui::SendProgressDialog *ui;
   // QString DestIp;
};

#endif // SENDPROGRESSDIALOG_H
