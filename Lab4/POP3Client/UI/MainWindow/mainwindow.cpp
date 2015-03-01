#include "mainwindow.h"

#include "email.h"
#include "emailwidget.h"
#include "pop3client.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      pop_(new POP3Client)
{
    connectEverything();
    pop_->Connect(QHostAddress("127.0.0.1"));
}

MainWindow::~MainWindow()
{
}

void MainWindow::connectEverything()
{
    connect(pop_, SIGNAL(OnConnect(QString)),
            this, SLOT(OnConnect(QString)));
    connect(pop_, SIGNAL(OnUser(bool)),
            this, SLOT(OnUser(bool)));
    connect(pop_, SIGNAL(OnPass(bool)),
            this, SLOT(OnPass(bool)));
    connect(pop_, SIGNAL(OnList(bool,QHash<int,int>)),
            this, SLOT(OnList(bool,QHash<int,int>)));
    connect(pop_, SIGNAL(OnStat(int,int)),
            this, SLOT(OnStat(int,int)));
    connect(pop_, SIGNAL(OnRetr(bool,Email)),
            this, SLOT(OnRetr(bool,Email)));
    connect(pop_, SIGNAL(OnDele(bool)),
            this, SLOT(OnDele(bool)));
    connect(pop_, SIGNAL(OnNoop()),
            this, SLOT(OnNoop()));
    connect(pop_, SIGNAL(OnQuit()),
            this, SLOT(OnQuit()));
}

void MainWindow::OnConnect(QString welcome)
{
    pop_->User("sup");
}

void MainWindow::OnUser(bool ok)
{
    pop_->Pass("sup");
}

void MainWindow::OnPass(bool ok)
{
    pop_->Retr(1);
}

void MainWindow::OnStat(int message_number, int octets)
{

}

void MainWindow::OnList(bool ok, QHash<int, int> messages)
{

}

void MainWindow::OnRetr(bool ok, Email email)
{
    EmailWidget* w = new EmailWidget(email);
    w->show();
}

void MainWindow::OnDele(bool ok)
{

}

void MainWindow::OnNoop()
{

}

void MainWindow::OnRset()
{

}

void MainWindow::OnQuit()
{

}
