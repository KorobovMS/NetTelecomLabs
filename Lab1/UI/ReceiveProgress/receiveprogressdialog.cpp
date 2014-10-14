#include "receiveprogressdialog.h"
#include "ui_receiveprogressdialog.h"

ReceiveProgressDialog::ReceiveProgressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReceiveProgressDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Recieving");
}

ReceiveProgressDialog::~ReceiveProgressDialog()
{
    delete ui;
}

void ReceiveProgressDialog::Progress(int r, int t)
{
    double percent = 100.0*r/t;
    ui->progressBar->setValue(static_cast<int>(percent));
}

void ReceiveProgressDialog::on_pushButtonCancel_clicked()
{
    close();
}
