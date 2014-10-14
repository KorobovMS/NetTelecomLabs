#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QThread>

#include "helpers.h"
#include "message.h"
#include "receivetransaction.h"
#include "server.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow),
    ip_was_configured_(false)
{
    ui_->setupUi(this);
    this->setWindowTitle("UDP client/server");
    qRegisterMetaType<QHostAddress>("QHostAddress");
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

    if (ip_was_configured_)
    {
        KillServer();
    }

    ip_was_configured_ = true;

    ui_->labelIp->setText(tr("Current Ip is: %1").arg(ip.toString()));
    ui_->labelPort->setText(tr("Current Port is: %1").arg(port));
    qDebug() << "Conf" << ip << port;
    QThread* server_thread = new QThread;
    Server* server = new Server;
    server->SetHostAddress(ip);
    server->SetPort(port);
    server->moveToThread(server_thread);

    connect(server_thread, SIGNAL(started()),
            server, SLOT(ServeForever()));

    connect(server,
            SIGNAL(NewRequest(QHostAddress,QHostAddress,quint16,QString,quint64,quint32)),
            this,
            SLOT(NewRequest(QHostAddress,QHostAddress,quint16,QString,quint64,quint32)));

    server_thread->start();
}

//Recieve
void MainWindow::NewRequest(QHostAddress host_addr, QHostAddress addr, quint16 port,
                                 QString filename, quint64 filesize,
                                 quint32 id)
{
    RequestToDownloadDialog *R = new RequestToDownloadDialog(this);
    connect(this,
            SIGNAL(TxDataToReqDialog(QHostAddress,QHostAddress,quint16,QString,quint64,quint32)),
            R,
            SLOT(RxDataFromMain(QHostAddress,QHostAddress,quint16,QString,quint64,quint32)));
    emit TxDataToReqDialog(host_addr, addr, port, filename, filesize, id);

    connect(R,
            SIGNAL(Accept(QHostAddress,QHostAddress,quint16,QString,quint64,quint32)),
            this,
            SLOT(RecieveAcceptSlot(QHostAddress,QHostAddress,quint16,QString,quint64,quint32)));

    connect(R, SIGNAL(Decline()), this, SLOT(RecieveDeclineSlot()));

    R->show();
    //R->setModal(true);
    //R->exec();
}

void MainWindow::RecieveAcceptSlot(QHostAddress host_addr, QHostAddress addr, quint16 port,
                                   QString filename, quint64 filesize,
                                   quint32 id)
{
    qDebug() << "RecieveAcceptSlot" << addr << port;
    ReceiveProgressDialog *RProrg = new ReceiveProgressDialog(this);

    QThread* worker_thread = new QThread;
    ReceiveTransaction* rt = new ReceiveTransaction(host_addr, addr, port, filename, filesize, id);

    rt->moveToThread(worker_thread);
    connect(worker_thread, SIGNAL(started()),
            rt, SLOT(Go()));

    connect(rt, SIGNAL(StartReceiving()),
            RProrg, SLOT(show()));
    connect(rt, SIGNAL(Progress(int,int)),
            RProrg, SLOT(Progress(int,int)));

    connect(rt, SIGNAL(FinishReceiving()),
            worker_thread, SLOT(quit()));
    connect(worker_thread, SIGNAL(finished()),
            worker_thread, SLOT(deleteLater()));
    connect(worker_thread, SIGNAL(finished()),
            rt, SLOT(deleteLater()));
    worker_thread->start();
}

void MainWindow::RecieveDeclineSlot()
{
}

void MainWindow::KillServer()
{
    Message kill_server(State::Request::KILL_YOURSELF, 0, 0, QByteArray());
    QByteArray kill_datagram;
    QDataStream kill_stream(&kill_datagram, QIODevice::ReadWrite);
    kill_stream << kill_server;
    stop_socket_.writeDatagram(kill_datagram, my_ip_, my_port_);
    stop_socket_.waitForBytesWritten();
}