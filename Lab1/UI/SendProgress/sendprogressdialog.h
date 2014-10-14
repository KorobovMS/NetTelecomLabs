#ifndef SENDPROGRESSDIALOG_H
#define SENDPROGRESSDIALOG_H

#include <QDialog>
#include <QHostAddress>
#include <QString>

namespace Ui {
class SendProgressDialog;
}

class SendProgressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SendProgressDialog(QWidget *parent = 0);
    ~SendProgressDialog();

private slots:
    void on_pushButtonCancel_clicked();

public slots:
    void RxDataFromSendDialog(QHostAddress DestIp, quint16 DestPort, QString DestFile);
    void Progress(int bytes_sent, int bytes_total);

signals:

private:
    Ui::SendProgressDialog *ui;
};

#endif // SENDPROGRESSDIALOG_H
