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
    ui_(new Ui::SendDialog)
{
    ui_->setupUi(this);
    this->setWindowTitle("Choose file to send");

    QRegExp re("(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}"
                 "([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])");
    ui_->lineEditIp->setValidator(new QRegExpValidator(re));
}

SendDialog::~SendDialog()
{
    delete ui_;
}

void SendDialog::on_toolButtonFile_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                ".",
                "All files (*.*)");
    ui_->lineEditFile->setText(filename);
}

void SendDialog::on_pushButtonOk_clicked()
{
    QString filename = ui_->lineEditFile->text();
    if (QFile::exists(filename))
    {
        QHostAddress dest_ip = QHostAddress(ui_->lineEditIp->text());
        bool ok;
        quint16 dest_port = ui_->lineEditPort->text().toUShort(&ok);
        if (!ok)
        {
            QMessageBox mb;
            mb.setWindowTitle(tr("Error"));
            mb.setText(tr("Port is not valid!"));
            mb.exec();
            return;
        }

        SendProgressDialog *progr = new SendProgressDialog(dest_ip, dest_port,
                                                           filename, this);
        QThread* worker_thread = new QThread;
        SendTransaction* st = new SendTransaction(dest_ip, dest_port,
                                                  FilePtr(new QFile(filename)));
        st->moveToThread(worker_thread);

        connect(worker_thread, SIGNAL(started()),
                st, SLOT(Go()));

        connect(st, SIGNAL(TransmissionStarted()),
                progr, SLOT(show()));
        connect(st, SIGNAL(TransmissionProgress(int,int)),
                progr, SLOT(Progress(int,int)));

        connect(st, SIGNAL(TransmissionFinished()),
                worker_thread, SLOT(quit()));
        connect(st, SIGNAL(TransmissionCancelled()),
                worker_thread, SLOT(quit()));
        connect(st, SIGNAL(TransmissionCancelled()),
                this, SLOT(TransmissionCancelled()));
        connect(st, SIGNAL(TransmissionFailed(quint32)),
                worker_thread, SLOT(quit()));
        connect(st, SIGNAL(TransmissionFailed(quint32)),
                this, SLOT(TransmissionFailed(quint32)));

        connect(worker_thread, SIGNAL(finished()),
                worker_thread, SLOT(deleteLater()));
        connect(worker_thread, SIGNAL(finished()),
                st, SLOT(deleteLater()));

        worker_thread->start();

        close();
    }
    else
    {
        QMessageBox msg;
        msg.setText(tr("Incorrect filepath"));
        msg.setWindowTitle(tr("Error"));
        msg.exec();
    }
}

void SendDialog::on_pushButtonCancel_clicked()
{
    close();
}

void SendDialog::TransmissionCancelled()
{
    QMessageBox mb;
    mb.setWindowTitle(tr("Warning"));
    mb.setText("File transmission was cancelled");
    mb.exec();
}

void SendDialog::TransmissionFailed(quint32 code)
{
    QMessageBox mb;
    mb.setWindowTitle(tr("Error"));
    mb.setText(tr("File transmission failed with error code %1").arg(code));
    mb.exec();
}
