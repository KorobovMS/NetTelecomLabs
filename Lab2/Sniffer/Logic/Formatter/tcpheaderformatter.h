#ifndef TCPHEADERFORMATTER_H
#define TCPHEADERFORMATTER_H

#include "formatter.h"
#include "tcpsegment.h"

/**
 * @brief The TCPHeaderFormatter class constructs string with TCP header fields
 */
class TCPHeaderFormatter : public Formatter
{
public:
    TCPHeaderFormatter(const TCPSegment& tcp);
    virtual const QString& GetString() const;

private:
    QString str_;
};

#endif // TCPHEADERFORMATTER_H
