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

void ReqToDLdialog::RxDataFromMain(QHostAddress addr, quint16 port,
                                   QString filename, quint64 filesize,
                                   quint32 id)
{
    addr_ = addr;
    port_ = port;
    filename_ = filename;
    filesize_ = filesize;
    id_ = id;

    ui->labelFilename->setText("Input file: " + filename_);
    ui->labelIp->setText("from: " + addr_ + ':' + port_);
}

void ReqToDLdialog::on_pushButtonAccept_clicked()
{
    emit Accept(addr_, port_, filename_, filesize_, id_);
    close();
}


void ReqToDLdialog::on_pushButtonDecline_clicked()
{
    emit Decline();
    close();
}
