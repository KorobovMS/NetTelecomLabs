#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHash>
#include <QHostAddress>
#include <QMainWindow>
#include <QUdpSocket>

#include "requestinfo.h"
#include "settings.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private slots:
    void on_actionSend_triggered();
    void on_actionConfigure_triggered();
    void on_actionKill_server_triggered();

    void IpAndPortConfigured(const QHostAddress& ip, quint16 port);
    void NewRequest(RequestInfo ri);
    void OnServerStartRunning(QHostAddress addr, quint16 port);
    void OnServerDead();
    void Configure();
    void RecieveAcceptSlot(quint32 id, QString dir);
    void RecieveDeclineSlot(quint32 id);

private:
    void RunServer();
    void KillServer();

private:
    Ui::MainWindow* ui_;

    QHostAddress my_ip_;
    quint16 my_port_;
    QUdpSocket stop_socket_;
    bool ip_was_configured_;
    QHash<quint32, RequestInfo> id2request_info_;
    Settings settings_;

    QString file_to_send_;
    QHostAddress ip_to_send_;
    quint16 port_to_send_;
};

#endif // MAINWINDOW_H
