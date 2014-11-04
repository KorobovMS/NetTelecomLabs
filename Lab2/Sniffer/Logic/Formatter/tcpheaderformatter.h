#ifndef TCPHEADERFORMATTER_H
#define TCPHEADERFORMATTER_H

#include <QString>
#include "formatter.h"
#include "tcpsegment.h"

class TCPHeaderFormatter : public Formatter
{
public:
    TCPHeaderFormatter(const TCPSegment& tcp);
    virtual const QString& GetString() const;

private:
    QString str_;
};

#endif // TCPHEADERFORMATTER_H
