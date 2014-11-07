#ifndef HEXDATAFORMATTER_H
#define HEXDATAFORMATTER_H

#include <QByteArray>
#include "bytearrayformatter.h"

/**
 * @brief The HexDataFormatter class constructs string with a table of hex data
 *        with 16 bytes in raw
 */
class HexDataFormatter : public ByteArrayFormatter
{
public:
    HexDataFormatter(const QByteArray& data = QByteArray());
    virtual const QString& GetString() const;
    virtual void SetData(const QByteArray& data);

private:
    QString str_;
};

#endif // HEXDATAFORMATTER_H
