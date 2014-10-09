#include "recieveprogressdialog.h"
#include "ui_recieveprogressdialog.h"

RecieveProgressDialog::RecieveProgressDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecieveProgressDialog)
{
    this->setWindowTitle("Recieving");
}

RecieveProgressDialog::~RecieveProgressDialog()
{
    delete ui;
}

void RecieveProgressDialog::Progress(int r, int t)
{
    double percent = 100.0*r/t;
    ui->progressBar->setValue(static_cast<int>(percent));
}

void RecieveProgressDialog::on_pushButtonCancel_clicked()
{
    close();
}
