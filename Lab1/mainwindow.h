#ifndef MAINWINDOW_H
#define MAINWINDOW_H
//главное окно
#include <QMainWindow>
#include "QStringList"
#include "senddialog.h"
#include "configdialog.h"
#include "reqtodldialog.h"
#include "recieveprogressdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString my_ip;
    QString my_port;

    QString file_to_send;
    QString ip_to_send;
    QString port_to_send;

private slots:
    void on_actionSend_triggered();  //нажали file-send

    void RecieveFileSlot(QString Ip, QString Port, QString FileName, QString Progress);//запрос на сохранение
    void RecieveAcceptSlot(); //согласились принять файл
    void RecieveDeclineSlot(); //оотклонили

    void on_actionConfigure_triggered(); //нажали Options-config
    void RecieveDataFromConfig(QString Ip, QString Port); //вывод нашего ип и порта в главное окно из конфиги



signals:
    void TxDataToReqDialog(QString Filename, QString Ip, QString Port);

};

#endif // MAINWINDOW_H
