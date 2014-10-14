#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QHostAddress>
#include <QMainWindow>
#include <QUdpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

signals:
    void DataToRequestDialog(QHostAddress addr, quint16 port, QString filename,
                           quint64 filesize, quint32 id);

private slots:
    void on_actionSend_triggered(); // File -> Send
    void on_actionConfigure_triggered(); // Options -> Config
    void IpAndPortConfigured(const QHostAddress& ip, quint16 port);
    void NewRequest(QHostAddress host, QHostAddress addr, quint16 port,
                    QString filename, quint64 filesize, quint32 id);
    void RecieveAcceptSlot(quint32 id);
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

    QString file_to_send_;
    QHostAddress ip_to_send_;
    quint16 port_to_send_;
};

#endif // MAINWINDOW_H
