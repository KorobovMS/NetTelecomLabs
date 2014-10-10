#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QHostAddress>
#include <QUdpSocket>

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
    QUdpSocket stop_socket_;
    bool ip_was_configured_;

    QString file_to_send_;
    QHostAddress ip_to_send_;
    quint16 port_to_send_;

private slots:
    void on_actionSend_triggered();  // File -> Send

    void NewRequest(QHostAddress host_addr, QHostAddress addr, quint16 port, QString filename,
                         quint64 filesize, quint32 id);
    void RecieveAcceptSlot(QHostAddress host_addr, QHostAddress addr, quint16 port, QString filename,
                           quint64 filesize, quint32 id);
    void RecieveDeclineSlot();

    void on_actionConfigure_triggered(); // Options -> Config
    void IpAndPortConfigured(const QHostAddress& ip, quint16 port);

private:
    void KillServer();

signals:
    void TxDataToReqDialog(QHostAddress host_addr, QHostAddress addr, quint16 port, QString filename,
                           quint64 filesize, quint32 id);
};

#endif // MAINWINDOW_H
