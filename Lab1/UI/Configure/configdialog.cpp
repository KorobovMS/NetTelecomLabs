#include "configdialog.h"
#include "ui_configdialog.h"

ConfigDialog::ConfigDialog(QWidget* parent) :
    QDialog(parent),
    ui_(new Ui::ConfigDialog)
{
    ui_->setupUi(this);
    this->setWindowTitle(tr("Configure IP/port"));
}

ConfigDialog::~ConfigDialog()
{
    delete ui_;
}

void ConfigDialog::on_okButton_clicked()
{
    emit DataIsValid(QHostAddress(ui_->lineEditIp->text()),
                     ui_->lineEditPort->text().toUShort());
    close();
}

void ConfigDialog::on_cancelButton_clicked()
{
    close();
}
