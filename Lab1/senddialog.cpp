#include "senddialog.h"
#include "ui_senddialog.h"
#include "QFileDialog"
#include "QFileSelector"
#include "QFile"
#include "QMessageBox"
#include "sendprogressdialog.h"

SendDialog::SendDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SendDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Chose file to send");
    //QRegExp IpExp("");
    //ui->lineEditIp->setValidator(new QRegExpValidator(IpExp, this));
}

SendDialog::~SendDialog()
{
    delete ui;
}

void SendDialog::on_toolButtonFile_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                "C:\\",
                "All files (*.*);;Text File (*.txt)");
    ui->lineEditFile->setText(filename);

}

void SendDialog::on_pushButtonOk_clicked()
{
    QString filename = ui->lineEditFile->text();
    if (QFile::exists(filename))
    {
        QString DestIp = ui->lineEditIp->text();
        QString DestPort = ui->lineEditPort->text();
        QString DestFile = ui->lineEditFile->text();

        SendProgressDialog *Progr = new SendProgressDialog(this);
        Progr->show();

        connect(this, SIGNAL(TxDataToProgrDialog(QString,QString,QString)),
                Progr, SLOT(RxDataFromSendDialog(QString,QString,QString)));
        emit TxDataToProgrDialog(DestIp, DestPort, DestFile);
        close();

    }
    else
    {
        QMessageBox msg;
        msg.setText("Incorrect filepath");
        msg.setWindowTitle("Error");
        msg.exec();
    }
}

void SendDialog::on_pushButtonCancel_clicked()
{
    close();
}


