#include "filetransfer.h"

#include <QDataStream>
#include <QFile>

FileTransfer::FileTransfer(QSharedPointer<QTcpSocket> sock, QString path,
                           int size, QObject *parent) :
    QObject(parent),
    sock_(sock),
    buf_size_(8192),
    path_(path),
    total_(size),
    bytes_read_(0)
{
}

void FileTransfer::Start()
{
    emit StartReceiving();
    QFile file(path_);
    file.open(QIODevice::WriteOnly);
    QDataStream stream(&file);

    while (!sock_->atEnd())
    {
        QByteArray data = sock_->read(buf_size_);
        if (data.size() <= 0)
        {
            break;
        }
        bytes_read_ += data.size();
        stream.writeRawData(data.data(), data.size());
        emit Percent(bytes_read_/total_);
    }
    emit EndReceiving();
}
