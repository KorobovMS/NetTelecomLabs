#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "filebrowser.h"
#include "ftp.h"

LogInWindow::LogInWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogInWindow),
    ftp_(new FTP)
{
    ui->setupUi(this);
    connect(this, SIGNAL(log_in_success()), this, SLOT(log_in_accept_slot()));
    connect(this, SIGNAL(log_in_decline()), this, SLOT(log_in_decline_slot()));
}

LogInWindow::~LogInWindow()
{
    delete ui;
}

void LogInWindow::on_pushButton_clicked()
{
    QString address = ui->lineEditAdress->text();
    connect(ftp_.data(), SIGNAL(Done(int,QString)),
            this, SLOT(OnConnect(int,QString)));
    ftp_->Connect(address);
}

void LogInWindow::OnConnect(int code, QString response)
{
    qDebug() << "OnConnect" << code << response;
    QString username = ui->lineEditUsername->text();
    disconnect(ftp_.data(), 0, 0, 0);
    connect(ftp_.data(), SIGNAL(Done(int,QString)),
            this, SLOT(OnUser(int,QString)));
    ftp_->User(username);
}

void LogInWindow::OnUser(int code, QString response)
{
    qDebug() << "OnUser" << code << response;
    QString password  = ui->lineEditPassword->text();
    disconnect(ftp_.data(), 0, 0, 0);
    connect(ftp_.data(), SIGNAL(Done(int,QString)),
            this, SLOT(OnPass(int,QString)));
    ftp_->Pass(password);
}

void LogInWindow::OnPass(int code, QString response)
{
    qDebug() << "OnPass" << code << response;
    emit log_in_success();
}

void LogInWindow::log_in_accept_slot()
{
    this->close();
    FileBrowser* f = new FileBrowser(ftp_);
    f->show();
}

void LogInWindow::log_in_decline_slot()
{
    ui->labelError->setText("Incorrect data");
}
