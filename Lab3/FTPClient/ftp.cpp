#include "ftp.h"

#include <QByteArray>
#include <QDataStream>
#include <QDebug>
#include <QHostInfo>
#include <QRegExp>
#include <QTcpSocket>
#include <QThread>

#include "filetransfer.h"

namespace
{
const QByteArray CRLF = "\r\n";
}

FTP::FTP(QObject* parent) :
    QObject(parent),
    sock_(0),
    is_passive_(true),
    is_executing_(false),
    is_pasv_sent_(false),
    is_anonymous_(false),
    data_channel_(0),
    data_channel_type_(eNone)
{
}

FTP::~FTP()
{
    Quit();
    delete sock_;
}

void FTP::Connect(const QString& host)
{
    QHostInfo info = QHostInfo::fromName(host);
    sock_ = new QTcpSocket;
    connect(sock_, SIGNAL(readyRead()),
            this, SLOT(controlReceived()));
    host_ = info.addresses().front();
    is_executing_ = true;
    sock_->connectToHost(host_, 21);
}

void FTP::User(const QString& user)
{
    is_anonymous_ = (user == "" || user == "anonymous");
    QString cmd = "USER " + (is_anonymous_ ? "anonymous" : user);
    command(cmd);
}

void FTP::Pass(const QString& password)
{
    QString pass;
    if (is_anonymous_ && (password.isEmpty() || password == "-"))
    {
        pass = password + "anonymous@";
    }
    QString cmd = "PASS " + pass;
    command(cmd);
}

void FTP::Acct(const QString& account)
{
    QString cmd = "ACCT " + account;
    command(cmd);
}

void FTP::Cwd(const QString& dirname)
{
    if (dirname == "..")
    {
        command("CDUP");
    }
    else
    {
        command("CWD " + (dirname == "" ? "." : dirname));
    }
}

void FTP::Pasv()
{
    is_pasv_sent_ = true;
    command("PASV");
}

void FTP::Pwd()
{
    command("PWD");
}

void FTP::Mlsd()
{
    data_channel_type_ = eLine;
    command("MLSD");
}

void FTP::Retrieve(const QString& filename, const QString& path_to_save)
{
    path_to_save_ = path_to_save;
    data_channel_type_ = eFile;
    command("RETR " + filename);
}

void FTP::SetActive()
{
    is_passive_ = false;
}

void FTP::SetPassive()
{
    is_passive_ = true;
}

void FTP::Abort()
{
    command("ABOR");
}

void FTP::Quit()
{
    command("QUIT");
}

void FTP::command(const QString& cmd)
{
    if (sock_ == 0)
    {
        emit CannotExecute();
        return;
    }

    if (is_executing_)
    {
        emit CommandIsExecuting();
        return;
    }

    forcedCommand(cmd);
}

void FTP::forcedCommand(const QString& cmd)
{
    QByteArray data;
    QDataStream stream(&data, QIODevice::ReadWrite);
    QByteArray command = cmd.toLatin1();
    stream.writeRawData(command.data(), command.size());
    stream.writeRawData(CRLF.data(), CRLF.size());
    sock_->write(data);
    is_executing_ = true;
}

QString FTP::getLine()
{
    QByteArray line = sock_->readLine();
    if (line.endsWith(CRLF))
    {
        return QString(line.left(line.size() - CRLF.size()));
    }
    else if (line.endsWith(CRLF[0]) || line.endsWith(CRLF[1]))
    {
        return QString(line.left(line.size() - 1));
    }
    else
    {
        return QString(line);
    }
}

QString FTP::getResponse(int& resp_code)
{
    QString response = getLine();
    resp_code = 0;
    if (response[3] == '-')
    {
        QString code = response.mid(0, 3);
        response = response.mid(4);
        resp_code = code.toInt();
        while (true)
        {
            QString next_line = getLine();
            if (next_line == "")
            {
                continue;
            }
            if (next_line.startsWith(code) && next_line[3] != '-')
            {
                break;
            }
            response += '\n';
            response += next_line.mid(4);
        }
    }
    return response;
}

void FTP::sendPort(const QHostAddress& host, quint16 port)
{
    QStringList bytes = host.toString().split('.');
    bytes.append(QString("%d").arg(port/256));
    bytes.append(QString("%d").arg(port%256));
    QString cmd = "PORT " + bytes.join(',');
    command(cmd);
}

void FTP::close()
{
    if (sock_)
    {
        sock_->close();
    }
}

void FTP::controlReceived()
{
    int code;
    QString response = getResponse(code);
    if (is_pasv_sent_ == true)
    {
        static QRegExp re227(tr("(\\d+),(\\d+),(\\d+),(\\d+),(\\d+),(\\d+)"));
        int pos = re227.indexIn(response);
        QStringList list = re227.capturedTexts();
        QString host = QStringList(list.mid(1, 4)).join('.');
        quint16 port = (list[5].toInt() << 8) + list[6].toInt();
        data_channel_.reset(new QTcpSocket);
        data_channel_->connectToHost(host, port);
        is_pasv_sent_ = false;
        is_executing_ = false;
        emit Done(code, response);
    }
    else if (data_channel_type_ != eNone)
    {
        DataChannelType type = data_channel_type_;
        data_channel_type_ = eNone;
        is_executing_ = false;
        if (!data_channel_)
        {
            emit CannotExecute();
        }
        else
        {
            if (type == eLine)
            {
                data_channel_->waitForReadyRead();
                QByteArray data = data_channel_->readAll();
                data_channel_.reset();
                sock_->readLine();
                emit Done(200, QString(data));
            }
            else if (type == eFile)
            {
                QSharedPointer<QTcpSocket> ptr = data_channel_;
                data_channel_.reset();
                emit NewFile(ptr);
            }
        }
    }
    else if (is_executing_)
    {
        is_executing_ = false;
        emit Done(code, response);
    }
}

void FTP::dataReceived()
{

}
