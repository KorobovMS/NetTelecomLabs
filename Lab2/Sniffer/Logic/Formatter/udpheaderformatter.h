#ifndef UDPHEADERFORMATTER_H
#define UDPHEADERFORMATTER_H

#include "formatter.h"
#include "udpsegment.h"

class UDPHeaderFormatter : public Formatter
{
public:
    UDPHeaderFormatter(const UDPSegment& udp);
    virtual const QString& GetString() const;

private:
    QString str_;
};

#endif // UDPHEADERFORMATTER_H
