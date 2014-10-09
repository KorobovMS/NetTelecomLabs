#include "senddialog.h"
#include "ui_senddialog.h"

#include <QHostAddress>
#include <QFileDialog>
#include <QFileSelector>
#include <QFile>
#include <QMessageBox>
#include <QThread>

#include "helpers.h"
#include "sendtransaction.h"
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
    filename = "C:/Users/user/Desktop/a.txt";
    if (QFile::exists(filename))
    {
        QHostAddress dest_ip = QHostAddress(ui->lineEditIp->text());
        quint16 dest_port = ui->lineEditPort->text().toUShort();

        SendProgressDialog *Progr = new SendProgressDialog(this);
        QThread* worker_thread = new QThread;
        QFile* file = new QFile(filename);
        file->moveToThread(worker_thread);
        SendTransaction* st = new SendTransaction(
                    QHostAddress("127.0.0.1"),
                    60001,
                    FilePtr(file));
        //SendTransaction* st = new SendTransaction(dest_ip, dest_port,
        //                                          FilePtr(new QFile(filename)));

        st->moveToThread(worker_thread);

        connect(worker_thread, SIGNAL(started()),
                st, SLOT(Go()));
        connect(st, SIGNAL(TransmissionStarted()),
                Progr, SLOT(show()));

        connect(st, SIGNAL(TransmissionProgress(int,int)),
                Progr, SLOT(Progress(int,int)));

        connect(st, SIGNAL(TransmissionFinished()),
                worker_thread, SLOT(quit()));
        connect(worker_thread, SIGNAL(finished()),
                worker_thread, SLOT(deleteLater()));
        connect(worker_thread, SIGNAL(finished()),
                st, SLOT(deleteLater()));

        worker_thread->start();

        connect(this, SIGNAL(TxDataToProgrDialog(QHostAddress,quint16,QString)),
                Progr, SLOT(RxDataFromSendDialog(QHostAddress,quint16,QString)));
        emit TxDataToProgrDialog(dest_ip, dest_port, filename);

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
