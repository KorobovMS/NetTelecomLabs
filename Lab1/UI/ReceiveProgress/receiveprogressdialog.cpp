#include "receiveprogressdialog.h"
#include "ui_receiveprogressdialog.h"

ReceiveProgressDialog::ReceiveProgressDialog(QHostAddress addr, quint16 port,
                                             QString name, QWidget* parent) :
    QDialog(parent),
    ui_(new Ui::ReceiveProgressDialog)
{
    ui_->setupUi(this);
    this->setWindowTitle("Recieving");
    ui_->labelFilename->setText(tr("Receiving %1").arg(name));
    ui_->labelIp->setText(tr("From %1:%2").arg(addr.toString()).arg(port));
}

ReceiveProgressDialog::~ReceiveProgressDialog()
{
    delete ui_;
}

void ReceiveProgressDialog::Progress(int r, int t)
{
    double percent = 100.0*r/t;
    ui_->progressBar->setValue(static_cast<int>(percent));
}

void ReceiveProgressDialog::on_pushButtonCancel_clicked()
{
    close();
}
