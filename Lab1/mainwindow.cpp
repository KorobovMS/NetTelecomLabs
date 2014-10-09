#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "senddialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("UDP client/server");
    on_actionConfigure_triggered(); //открытие конфиги при запуске
    //RecieveFileSlot("12", "12", "12", "12"); //тест окна

    //connect(this, SIGNAL(*lol*),
    //        this, SLOT(RecieveFileSlot(QString,QString,QString,QString))); //Коннект для приёма файлов
}

MainWindow::~MainWindow()
{
    delete ui;
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
    connect(Config, SIGNAL(DataIsValid(QString,QString)), this, SLOT(RecieveDataFromConfig(QString,QString)));
    Config->setModal(true);
    Config->exec();
}
void MainWindow::RecieveDataFromConfig(QString Ip, QString Port)
{
    my_ip = Ip;
    my_port = Port;
    ui->labelIp->setText("Current Ip is: " + Ip);
    ui->labelPort->setText("Current Port is: " + Port);
    //
    //RecieveFileSlot("12", "12", "12", "12"); //тест окна
}

//Reciev
void MainWindow::RecieveFileSlot(QString Ip, QString Port, QString FileName, QString Progress) //Слот для входящего файла. Отсуда вызывается ацепт\деклайн
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
