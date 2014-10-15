#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QThread>

#include "configdialog.h"
#include "helpers.h"
#include "receiveprogressdialog.h"
#include "receivetransaction.h"
#include "confirmuploaddialog.h"
#include "senddialog.h"
#include "server.h"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui_(new Ui::MainWindow),
    ip_was_configured_(false)
{
    ui_->setupUi(this);
    this->setWindowTitle(tr("UDP client/server"));
    qRegisterMetaType<QHostAddress>("QHostAddress");
    on_actionConfigure_triggered();
}

MainWindow::~MainWindow()
{
    delete ui_;
}

// Send
void MainWindow::on_actionSend_triggered()
{
    SendDialog* send_window = new SendDialog(this);
    send_window->setModal(true);
    send_window->exec();
}

// Config
void MainWindow::on_actionConfigure_triggered()
{
    ConfigDialog* config = new ConfigDialog(this);
    connect(config, SIGNAL(DataIsValid(QHostAddress,quint16)),
            this, SLOT(IpAndPortConfigured(QHostAddress,quint16)));
    config->setModal(true);
    config->exec();
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

    RunServer();
}

// Recieve
void MainWindow::NewRequest(RequestInfo ri)
{
    ConfirmUploadDialog* confirm_dlg =
            new ConfirmUploadDialog(ri.client_ip_, ri.client_port_,
                                    ri.filename_, ri.filesize_, ri.id_, this);

    id2request_info_.insert(ri.id_, ri);

    connect(confirm_dlg,
            SIGNAL(Accept(quint32)),
            this,
            SLOT(RecieveAcceptSlot(quint32)));
    connect(confirm_dlg, SIGNAL(Decline(quint32)),
            this, SLOT(RecieveDeclineSlot(quint32)));

    confirm_dlg->show();
}

void MainWindow::RecieveAcceptSlot(quint32 id)
{
    RequestInfo ri = id2request_info_[id];

    ReceiveProgressDialog* RProrg =
            new ReceiveProgressDialog(ri.client_ip_, ri.client_port_,
                                      ri.filename_, this);
    QThread* worker_thread = new QThread;
    ReceiveTransaction* rt = new ReceiveTransaction(ri);
    id2request_info_.remove(id);
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

void MainWindow::RecieveDeclineSlot(quint32 id)
{
    id2request_info_.remove(id);
}

// Server lifecycle
void MainWindow::RunServer()
{
    QThread* server_thread = new QThread;
    Server* server = new Server;
    server->SetHostAddress(my_ip_);
    server->SetPort(my_port_);
    server->moveToThread(server_thread);

    connect(server_thread, SIGNAL(started()),
            server, SLOT(ServeForever()));
    connect(server,
            SIGNAL(NewRequest(RequestInfo)),
            this,
            SLOT(NewRequest(RequestInfo)));
    connect(server, SIGNAL(Dead()),
            server_thread, SLOT(quit()));
    connect(server_thread, SIGNAL(finished()),
            server_thread, SLOT(deleteLater()));
    connect(server_thread, SIGNAL(finished()),
            server, SLOT(deleteLater()));

    server_thread->start();
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
