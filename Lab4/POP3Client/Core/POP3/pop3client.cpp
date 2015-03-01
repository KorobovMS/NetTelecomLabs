#include "pop3client.h"

#include <QByteArray>
#include <QTcpSocket>

namespace
{
const QString CRLF = "\r\n";
}

POP3Client::POP3Client(QObject *parent) :
    QObject(parent),
    sock_(new QTcpSocket),
    current_cmd_(eNone)
{
}

POP3Client::~POP3Client()
{
    delete sock_;
}

void POP3Client::Connect(const QHostAddress& addr, quint16 port)
{
    connect(sock_, SIGNAL(readyRead()),
            this, SLOT(onDataReceived()));
    current_cmd_ = eConnect;
    sock_->connectToHost(addr, port);
}

void POP3Client::User(const QString& name)
{
    current_cmd_ = eUser;
    command(QString("USER %1").arg(name));
}

void POP3Client::Pass(const QString& password)
{
    current_cmd_ = ePass;
    command(QString("PASS %1").arg(password));
}

void POP3Client::Stat()
{
    current_cmd_ = eStat;
    command(QString("STAT"));
}

void POP3Client::List()
{
    current_cmd_ = eList;
    command(QString("LIST"));
}

void POP3Client::Retr(int msg)
{
    current_cmd_ = eRetr;
    retr_number_ = msg;
    command(QString("RETR %1").arg(msg));
}

void POP3Client::Dele(int msg)
{
    current_cmd_ = eDele;
    command(QString("DELE %1").arg(msg));
}

void POP3Client::Noop()
{
    current_cmd_= eNoop;
    command(QString("NOOP"));
}

void POP3Client::Rset()
{
    current_cmd_ = eRset;
    command(QString("RSET"));
}

void POP3Client::Quit()
{
    command(QString("QUIT"));
    sock_->disconnectFromHost();
}

void POP3Client::onDataReceived()
{
    Command cmd = current_cmd_;
    current_cmd_ = eNone;
    switch (cmd)
    {
    case eConnect:
        processConnect();
        break;

    case eUser:
        processUser();
        break;

    case ePass:
        processPass();
        break;

    case eStat:
        processStat();
        break;

    case eList:
        processList();
        break;

    case eRetr:
        processRetr();
        break;

    case eDele:
        processDele();
        break;

    case eNoop:
        processNoop();
        break;

    case eRset:
        processRset();
        break;
    }
}

QString POP3Client::getLine()
{
    QString line = QString(sock_->readLine());
    if (line.endsWith(CRLF))
    {
        return line.left(line.length() - CRLF.length());
    }

    if (line[0] == CRLF[0])
    {
        return line.mid(1, line.length() - 1);
    }

    return line.left(line.length() - 1);
}

QString POP3Client::getResponse()
{
    return getLine();
}

QString POP3Client::getLongResponse(QVector<QString>& lst)
{
    lst.clear();
    QString resp = getResponse();
    if (resp.startsWith("-ERR"))
    {
        return resp;
    }

    QString line = getLine();
    while (line != ".")
    {
        if (line.startsWith(".."))
        {
            line = line.mid(1);
        }
        lst.append(line + "\n");
        line = getLine();
    }
    return resp;
}

void POP3Client::command(const QString& cmd)
{
    if (current_cmd_ != eNone)
    {
        QByteArray utf8data = (cmd + CRLF).toUtf8();
        sock_->write(utf8data);
        sock_->waitForBytesWritten();
    }
}

void POP3Client::processConnect()
{
    QString welcome = getResponse();
    qDebug() << "Connect:" << welcome;
    emit OnConnect(welcome.mid(4));
}

void POP3Client::processUser()
{
    QString resp = getResponse();
    qDebug() << "USER:" << resp;
    emit OnUser(resp.startsWith("+OK"));
}

void POP3Client::processPass()
{
    QString resp = getResponse();
    qDebug() << "PASS:" << resp;
    emit OnPass(resp.startsWith("+OK"));
}

void POP3Client::processStat()
{
    QString resp = getResponse();
    QStringList lst = resp.split(" ");
    qDebug() << "STAT:" << resp;
    emit OnStat(lst[1].toInt(), lst[2].toInt());
}

void POP3Client::processList()
{
    QVector<QString> lst;
    QString resp = getLongResponse(lst);
    QHash<int, int> messages;
    QVector<QString>::const_iterator it = lst.cbegin();
    for (; it != lst.cend(); ++it)
    {
        QStringList pair = it->split(" ");
        messages.insert(pair[0].toInt(), pair[1].toInt());
    }
    qDebug() << "LIST:" << resp << lst;
    emit OnList(resp.startsWith("+OK"), messages);
}

void POP3Client::processRetr()
{
    QVector<QString> lst;
    QString resp = getLongResponse(lst);
    QHash<QString, QString> headers;
    QString body;
    QVector<QString>::const_iterator it = lst.cbegin();
    while (it != lst.cend() && !it->isEmpty())
    {
        QStringList pair = it->split(": ");
        headers.insert(pair[0], pair[1]);
        ++it;
    }

    if (it != lst.cend())
    {
        for (; it != lst.cend(); ++it)
        {
            body += *it;
        }
    }
    qDebug() << "RETR:" << resp << lst;
    emit OnRetr(resp.startsWith("+OK"), Email(retr_number_, headers, body));
}

void POP3Client::processDele()
{
    QString resp = getResponse();
    qDebug() << "DELE:" << resp;
    emit OnDele(resp.startsWith("+OK"));
}

void POP3Client::processNoop()
{
    QString resp = getResponse();
    qDebug() << "NOOP:" << resp;
    emit OnNoop();
}

void POP3Client::processRset()
{
    QString resp = getResponse();
    qDebug() << "RSET:" << resp;
    emit OnRset();
}
