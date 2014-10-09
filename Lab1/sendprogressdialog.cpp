#include "sendprogressdialog.h"
#include "ui_sendprogressdialog.h"

SendProgressDialog::SendProgressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SendProgressDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Sending");
}

SendProgressDialog::~SendProgressDialog()
{
    delete ui;
}

void SendProgressDialog::on_pushButtonCancel_clicked()
{
    close();
}

void SendProgressDialog::RxDataFromSendDialog(QString DestIp, QString DestPort, QString DestFile)
{
    QString s = "to " + DestIp + ':' + DestPort;
    ui->labelIp->setText(s);
    ui->labelFilename->setText("Send " + DestFile);
}
