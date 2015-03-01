#ifndef FILETRANSFER_H
#define FILETRANSFER_H

#include <QObject>
#include <QSharedPointer>
#include <QTcpSocket>

class FileTransfer : public QObject
{
    Q_OBJECT

public:
    explicit FileTransfer(QSharedPointer<QTcpSocket> sock, QString path,
                          int size, QObject *parent = 0);

public slots:
    void Start();

signals:
    void StartReceiving();
    void Percent(int p);
    void EndReceiving();

private:
    QSharedPointer<QTcpSocket> sock_;
    const int buf_size_;
    QString path_;
    int total_;
    int bytes_read_;
};

#endif // FILETRANSFER_H
