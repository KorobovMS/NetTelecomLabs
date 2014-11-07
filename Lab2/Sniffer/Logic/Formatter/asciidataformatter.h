#ifndef ASCIIDATAFORMATTER_H
#define ASCIIDATAFORMATTER_H

#include "bytearrayformatter.h"

/**
 * @brief The AsciiDataFormatter class converts QByteArray to ascii string
 */
class AsciiDataFormatter : public ByteArrayFormatter
{
public:
    AsciiDataFormatter(const QByteArray& data = QByteArray());
    virtual const QString& GetString() const;
    virtual void SetData(const QByteArray& data);

private:
    QString str_;
};

#endif // ASCIIDATAFORMATTER_H
