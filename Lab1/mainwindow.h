#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QHostAddress>

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
    Ui::MainWindow* ui_;
    QHostAddress my_ip_;
    quint16 my_port_;

    QString file_to_send_;
    QHostAddress ip_to_send_;
    quint16 port_to_send_;

private slots:
    void on_actionSend_triggered();  // File -> Send

    void RecieveFileSlot(QString Ip, QString Port, QString FileName, QString Progress);
    void RecieveAcceptSlot();
    void RecieveDeclineSlot();

    void on_actionConfigure_triggered(); // Options -> Config
    void IpAndPortConfigured(const QHostAddress& ip, quint16 port);

signals:
    void TxDataToReqDialog(QString Filename, QString Ip, QString Port);
};

#endif // MAINWINDOW_H
