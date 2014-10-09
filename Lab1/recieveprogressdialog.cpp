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

void RecieveProgressDialog::on_pushButtonCancel_clicked()
{
    close();
}
