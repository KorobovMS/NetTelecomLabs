#ifndef FTP_H
#define FTP_H

#include <QHostAddress>
#include <QObject>
#include <QSharedPointer>
#include <QString>

class QTcpSocket;
class FileTransfer;

enum Command
{
    eConnect,
    eLogin,
    eCwd,
    ePwd,
    eRetrieve,
    eQuit,
    eAbort
};

enum DataChannelType
{
    eNone,
    eLine,
    eFile,
};

class FTP : public QObject
{
    Q_OBJECT

public:
    explicit FTP(QObject* parent = 0);
    ~FTP();

    void Connect(const QString& host);
    void User(const QString& user = "");
    void Pass(const QString& password = "");
    void Acct(const QString& account = "");
    void Cwd(const QString& dirname = "");
    void Pasv();
    void Pwd();
    void Mlsd();
    void Retrieve(const QString& filename, const QString& path_to_save);
    void SetActive();
    void SetPassive();
    void Abort();
    void Quit();

signals:
    void Done(int code, QString response);
    void NewFile(QSharedPointer<QTcpSocket> sock);
    void CannotExecute();
    void CommandIsExecuting();

private:
    void command(const QString& cmd);
    void forcedCommand(const QString& cmd);
    QString getLine();
    QString getResponse(int& resp_code);
    void sendPort(const QHostAddress& host, quint16 port);
    void close();

private slots:
    void controlReceived();
    void dataReceived();

private:
    QTcpSocket* sock_;
    bool is_passive_;
    QHostAddress host_;
    bool is_executing_;
    bool is_pasv_sent_;
    bool is_anonymous_;
    DataChannelType data_channel_type_;
    QSharedPointer<QTcpSocket> data_channel_;
    QString path_to_save_;
};

void Parse227(const QString& response, QHostAddress& addr, quint16& port);

#endif // FTP_H
