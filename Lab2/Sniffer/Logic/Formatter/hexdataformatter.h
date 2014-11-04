#ifndef HEXDATAFORMATTER_H
#define HEXDATAFORMATTER_H

#include <QByteArray>
#include "formatter.h"

/**
 * @brief The HexDataFormatter class constructs string with a table of hex data
 *        with 16 bytes in raw
 */
class HexDataFormatter : public Formatter
{
public:
    HexDataFormatter(const QByteArray& data);
    virtual const QString& GetString() const;

private:
    QString str_;
};

#endif // HEXDATAFORMATTER_H
