#ifndef IPHEADERFORMATTER_H
#define IPHEADERFORMATTER_H

#include "formatter.h"
#include "ippacket.h"

/**
 * @brief The IPHeaderFormatter class constructs string with IP header fields
 */
class IPHeaderFormatter : public Formatter
{
public:
    IPHeaderFormatter(const IPPacket& ip);
    virtual const QString& GetString() const;

private:
    QString str_;
};

#endif // IPHEADERFORMATTER_H
