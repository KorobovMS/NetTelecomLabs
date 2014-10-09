#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow)
{
    ui_->setupUi(this);
    this->setWindowTitle("UDP client/server");
    on_actionConfigure_triggered();
}

MainWindow::~MainWindow()
{
    delete ui_;
}

//Send
void MainWindow::on_actionSend_triggered()
{
    SendDialog *SendWindow = new SendDialog(this);
    SendWindow->setModal(true);
    SendWindow->exec();
}

//config
void MainWindow::on_actionConfigure_triggered()
{
    ConfigDialog *Config = new ConfigDialog(this);
    connect(Config, SIGNAL(DataIsValid(QHostAddress,quint16)),
            this, SLOT(IpAndPortConfigured(QHostAddress,quint16)));
    Config->setModal(true);
    Config->exec();
}

void MainWindow::IpAndPortConfigured(const QHostAddress& ip, quint16 port)
{
    my_ip_ = ip;
    my_port_ = port;
    ui_->labelIp->setText(tr("Current Ip is: %1").arg(ip.toString()));
    ui_->labelPort->setText(tr("Current Port is: %1").arg(port));
}

//Recieve
void MainWindow::RecieveFileSlot(QString Ip, QString Port, QString FileName, QString Progress)
{
    ReqToDLdialog *R = new ReqToDLdialog(this);
    emit(TxDataToReqDialog(FileName, Ip, Port));
    connect(R, SIGNAL(Accept()), this, SLOT(RecieveAcceptSlot()));
    connect(R, SIGNAL(Decline()), this, SLOT(RecieveDeclineSlot()));
    R->setModal(true);
    R->exec();
}

void MainWindow::RecieveAcceptSlot()
{
    RecieveProgressDialog *RProrg = new RecieveProgressDialog(this);
    //тут должен быть коннект на сигнал, передающий данные на окно прогресса загрузки
    RProrg->show();
}

void MainWindow::RecieveDeclineSlot()
{

}
