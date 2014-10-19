#include "confirmuploaddialog.h"
#include "ui_confirmuploaddialog.h"

#include <QFileDialog>

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

    QString dir;
    s_.GetDownloads(dir);
    ui_->lineEditLocation->setText(dir);

}

ConfirmUploadDialog::~ConfirmUploadDialog()
{
    delete ui_;
}

void ConfirmUploadDialog::on_pushButtonAccept_clicked()
{
    QString dir = QDir::cleanPath(ui_->lineEditLocation->text());
    if (QDir().mkpath(dir))
    {
        emit Accept(id_, dir);
        close();
    }
}

void ConfirmUploadDialog::on_pushButtonDecline_clicked()
{
    emit Decline(id_);
    close();
}

void ConfirmUploadDialog::on_toolButton_clicked()
{
    QString first_dir;
    s_.GetDownloads(first_dir);
    QString dir = QFileDialog::getExistingDirectory(
                0,
                tr("Select downloads folder"),
                first_dir);
    ui_->lineEditLocation->setText(dir);
}
