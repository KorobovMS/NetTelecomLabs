#include "reqtodldialog.h"
#include "ui_reqtodldialog.h"

ReqToDLdialog::ReqToDLdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ReqToDLdialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Incoming file");
}

ReqToDLdialog::~ReqToDLdialog()
{
    delete ui;
}
/*
void ReqToDLdialog::RxDataFromMain(QString Filename, QString Ip, QString Port)
{
    ui->labelFilename->setText("Input file: " + Filename);
    ui->labelIp->setText("from: " + Ip + ':' + Port);
}
*/

void ReqToDLdialog::on_pushButtonAccept_clicked()
{
    emit(Accept());
    close();
}


void ReqToDLdialog::on_pushButtonDecline_clicked()
{
    emit(Decline());
    close();
}
