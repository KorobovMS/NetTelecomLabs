#ifndef HELPERS_H
#define HELPERS_H

#include <QFile>
#include <QSharedPointer>

typedef QSharedPointer<QFile> FilePtr;

namespace State
{
namespace Request
{
const quint32 REQ_ID = 0;
const quint32 SEND_DATA = 3;
const quint32 SEND_FINISH = 6;
}

namespace Response
{
const quint32 RESP_ID = 1;
const quint32 RECV_DATA = 4;
const quint32 RECV_FINISH = 7;
}

namespace Error
{
const quint32 ID_RECEIVING_FAILED = 2;
const quint32 SEND_DATA_FAILED = 5;
const quint32 FINISH_FAILED = 8;
}
}

#endif // HELPERS_H
