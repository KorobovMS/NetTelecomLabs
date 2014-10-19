#include "configdialog.h"
#include "ui_configdialog.h"

ConfigDialog::ConfigDialog(QWidget* parent) :
    QDialog(parent),
    ui_(new Ui::ConfigDialog)
{
    ui_->setupUi(this);
    this->setWindowTitle(tr("Configure IP/port"));

    QRegExp re("(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.){3}"
                 "([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])");
    ui_->lineEditIp->setValidator(new QRegExpValidator(re));

    QHostAddress ip;
    if (s_.GetIP(ip))
    {
        ui_->lineEditIp->setText(ip.toString());
    }

    quint16 port;
    if (s_.GetPort(port))
    {
        ui_->lineEditPort->setText(tr("%1").arg(port));
    }
}

ConfigDialog::~ConfigDialog()
{
    delete ui_;
}

void ConfigDialog::on_okButton_clicked()
{
    QHostAddress addr(ui_->lineEditIp->text());
    bool ok;
    quint16 port = ui_->lineEditPort->text().toUShort(&ok);
    if (!addr.isNull() && ok)
    {
        if (ui_->SaveAsDefault->isChecked())
        {
            s_.SetIP(addr);
            s_.SetPort(port);
        }

        emit DataIsValid(addr, port);
        close();
    }
}

void ConfigDialog::on_cancelButton_clicked()
{
    close();
}
