#include "configdialog.h"
#include "ui_configdialog.h"

ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Configure IP/port");
}

ConfigDialog::~ConfigDialog()
{
    delete ui;
}

void ConfigDialog::on_pushButtonOk_clicked()
{
    //validation -------


    // ---------
    emit DataIsValid(QHostAddress(ui->lineEditIp->text()),
                     ui->lineEditPort->text().toUShort());
    close();
}

void ConfigDialog::on_pushButton_2_clicked()
{
    close();
}
