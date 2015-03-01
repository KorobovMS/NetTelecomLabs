#ifndef POP3CLIENT_H
#define POP3CLIENT_H

#include <QHash>
#include <QHostAddress>
#include <QObject>
#include <QString>
#include <QVector>

#include "email.h"

enum Command
{
    eNone,
    eConnect,
    eUser,
    ePass,
    eStat,
    eList,
    eRetr,
    eDele,
    eNoop,
    eRset,
};

class QTcpSocket;

class POP3Client : public QObject
{
    Q_OBJECT

public:
    explicit POP3Client(QObject* parent = 0);
    ~POP3Client();

    void Connect(const QHostAddress& addr, quint16 port = 110);
    void User(const QString& name);
    void Pass(const QString& password);
    void Stat();
    void List();
    void Retr(int msg);
    void Dele(int msg);
    void Noop();
    void Rset();
    void Quit();

signals:
    void OnConnect(QString welcome);
    void OnUser(bool ok);
    void OnPass(bool ok);
    void OnStat(int message_number, int octets);
    void OnList(bool ok, QHash<int, int> messages);
    void OnRetr(bool ok, Email email);
    void OnDele(bool ok);
    void OnNoop();
    void OnRset();
    void OnQuit();

private slots:
    void onDataReceived();

private:
    QString getLine();
    QString getResponse();
    QString getLongResponse(QVector<QString>& lst);
    void command(const QString& cmd);
    void processConnect();
    void processUser();
    void processPass();
    void processStat();
    void processList();
    void processRetr();
    void processDele();
    void processNoop();
    void processRset();

private:
    QTcpSocket* sock_;
    Command current_cmd_;
    int retr_number_;
};

#endif // POP3CLIENT_H
