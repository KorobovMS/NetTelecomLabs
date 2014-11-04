#ifndef ICMPHEADERFORMATTER_H
#define ICMPHEADERFORMATTER_H

#include "formatter.h"
#include "icmpsegment.h"

/**
 * @brief The ICMPHeaderFormatter class constructs string
 *        with ICMP header fields
 */
class ICMPHeaderFormatter : public Formatter
{
public:
    ICMPHeaderFormatter(const ICMPSegment& icmp);
    virtual const QString& GetString() const;

private:
    QString str_;
};

#endif // ICMPHEADERFORMATTER_H
