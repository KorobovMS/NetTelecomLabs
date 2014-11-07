#ifndef BYTEARRAYFORMATTER_H
#define BYTEARRAYFORMATTER_H

#include <QByteArray>
#include <QSharedPointer>

#include "formatter.h"

class ByteArrayFormatter : public Formatter
{
public:
    virtual void SetData(const QByteArray& data) = 0;
};

typedef QSharedPointer<ByteArrayFormatter> ByteArrayFormatterPtr;

#endif // BYTEARRAYFORMATTER_H
