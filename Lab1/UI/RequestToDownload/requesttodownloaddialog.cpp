#include "requesttodownloaddialog.h"
#include "ui_reqtodldialog.h"

RequestToDownloadDialog::RequestToDownloadDialog(QWidget *parent) :
    QDialog(parent),
    ui_(new Ui::RequestToDownloadDialog)
{
    ui_->setupUi(this);
    this->setWindowTitle(tr("Incoming file"));
}

RequestToDownloadDialog::~RequestToDownloadDialog()
{
    delete ui_;
}

void RequestToDownloadDialog::RxDataFromMain(QHostAddress addr, quint16 port,
                                   QString filename, quint64 filesize,
                                   quint32 id)
{
    id_ = id;

    ui_->labelFilename->setText(tr("Input file: %1 (%2 bytes)")
                                .arg(filename)
                                .arg(filesize));
    ui_->labelIp->setText(tr("From: %1:%2").arg(addr.toString()).arg(port));
}

void RequestToDownloadDialog::on_pushButtonAccept_clicked()
{
    emit Accept(id_);
    close();
}


void RequestToDownloadDialog::on_pushButtonDecline_clicked()
{
    emit Decline(id_);
    close();
}
