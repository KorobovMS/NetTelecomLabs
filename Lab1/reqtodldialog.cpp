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

void ReqToDLdialog::RxDataFromMain(QHostAddress host_addr, QHostAddress addr, quint16 port,
                                   QString filename, quint64 filesize,
                                   quint32 id)
{
    qDebug() << "RxDataFromMain" << addr << port;
    host_addr_ = host_addr;
    addr_ = addr;
    port_ = port;
    filename_ = filename;
    filesize_ = filesize;
    id_ = id;

    ui->labelFilename->setText("Input file: " + filename_);
    ui->labelIp->setText("from: " + addr_.toString() + ':' + tr("%1").arg(port_));
}

void ReqToDLdialog::on_pushButtonAccept_clicked()
{
    emit Accept(host_addr_, addr_, port_, filename_, filesize_, id_);
    close();
}


void ReqToDLdialog::on_pushButtonDecline_clicked()
{
    emit Decline();
    close();
}
