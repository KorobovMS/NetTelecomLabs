#ifndef HEXDATAFORMATTER_H
#define HEXDATAFORMATTER_H

#include <QByteArray>
#include "formatter.h"

class HexDataFormatter : public Formatter
{
public:
    HexDataFormatter(const QByteArray& data);
    virtual const QString& GetString() const;

private:
    QString str_;
};

#endif // HEXDATAFORMATTER_H
