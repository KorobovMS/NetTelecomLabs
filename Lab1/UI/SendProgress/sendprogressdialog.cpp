#include "sendprogressdialog.h"
#include "ui_sendprogressdialog.h"

SendProgressDialog::SendProgressDialog(QHostAddress ip, quint16 port,
                                       QString filename, QWidget* parent) :
    QDialog(parent),
    ui_(new Ui::SendProgressDialog)
{
    ui_->setupUi(this);
    this->setWindowTitle("Sending...");
    ui_->labelIp->setText(tr("To %1:%2").arg(ip.toString()).arg(port));
    ui_->labelFilename->setText(tr("Sending %1").arg(filename));
}

SendProgressDialog::~SendProgressDialog()
{
    delete ui_;
}

void SendProgressDialog::on_pushButtonCancel_clicked()
{
    close();
}

void SendProgressDialog::Progress(int bytes_sent, int bytes_total)
{
    double percent = 100.0*bytes_sent/bytes_total;
    ui_->progressBar->setValue(static_cast<int>(percent));
}
