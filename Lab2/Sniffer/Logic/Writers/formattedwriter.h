#ifndef FORMATTEDWRITER_H
#define FORMATTEDWRITER_H

#include <QSharedPointer>

#include "bytearrayformatter.h"
#include "writer.h"

class FormattedWriter : public Writer
{
public:
    FormattedWriter(ByteArrayFormatterPtr formatter);
    virtual void WriteString(const QString& str) = 0;
    virtual void WriteBytes(const QByteArray& arr);

protected:
    ByteArrayFormatterPtr formatter_;
};

#endif // FORMATTEDWRITER_H
