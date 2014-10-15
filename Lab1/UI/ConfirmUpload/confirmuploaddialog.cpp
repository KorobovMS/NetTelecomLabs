#include "confirmuploaddialog.h"
#include "ui_confirmuploaddialog.h"

ConfirmUploadDialog::ConfirmUploadDialog(QHostAddress ip, quint16 port,
                                         QString filename, quint64 filesize,
                                         quint32 id, QWidget* parent) :
    QDialog(parent),
    ui_(new Ui::ConfirmUploadDialog)
{
    ui_->setupUi(this);
    this->setWindowTitle(tr("Incoming file"));
    id_ = id;
    ui_->labelFilename->setText(tr("Input file: %1 (%2 bytes)")
                                .arg(filename)
                                .arg(filesize));
    ui_->labelIp->setText(tr("From: %1:%2").arg(ip.toString()).arg(port));
}

ConfirmUploadDialog::~ConfirmUploadDialog()
{
    delete ui_;
}

void ConfirmUploadDialog::on_pushButtonAccept_clicked()
{
    emit Accept(id_);
    close();
}

void ConfirmUploadDialog::on_pushButtonDecline_clicked()
{
    emit Decline(id_);
    close();
}
