#include "sendprogressdialog.h"
#include "ui_sendprogressdialog.h"

SendProgressDialog::SendProgressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SendProgressDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Sending...");
}

SendProgressDialog::~SendProgressDialog()
{
    delete ui;
}

void SendProgressDialog::on_pushButtonCancel_clicked()
{
    close();
}

void SendProgressDialog::RxDataFromSendDialog(QHostAddress DestIp, quint16 DestPort, QString DestFile)
{
    QString s = "to " + DestIp.toString() + ':' + tr("%1").arg(DestPort);
    ui->labelIp->setText(s);
    ui->labelFilename->setText("Send " + DestFile);
}

void SendProgressDialog::Progress(int bytes_sent, int bytes_total)
{
    double percent = 100.0*bytes_sent/bytes_total;
    ui->progressBar->setValue(static_cast<int>(percent));
}
