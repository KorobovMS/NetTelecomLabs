#include "filterstorage.h"

#include <QJsonArray>
#include <QJsonObject>

#include "jsonutils.h"
#include "ippacket.h"

FilterStorage::FilterStorage(const QJsonArray& array)
{
    QJsonArray::const_iterator it = array.begin();
    for (; it != array.end(); ++it)
    {
        QJsonObject filter_obj = (*it).toObject();
        Filter filter;

        QString type;
        if (!GetJSONString(filter_obj, "type", type))
        {
            continue;
        }

        QString writer;
        if (!GetJSONString(filter_obj, "writer", writer))
        {
            continue;
        }
        filter.SetWriter(writer);

        QString from;
        if (GetJSONString(filter_obj, "from", from))
        {
            filter.SetFrom(QHostAddress(from));
        }

        QString to;
        if (GetJSONString(filter_obj, "to", to))
        {
            filter.SetTo(QHostAddress(to));
        }

        if (type == "raw")
        {
            raw_filters_.append(filter);
        }
        else if (type == "ip")
        {
            ip_filters_.append(filter);
        }
        else if (type == "icmp")
        {
            protocol_to_filters_[Protocols::ICMP].append(filter);
        }
        else if (type == "udp")
        {
            protocol_to_filters_[Protocols::UDP].append(filter);
        }
        else if (type == "tcp")
        {
            protocol_to_filters_[Protocols::TCP].append(filter);
        }
    }
}

const Filters&FilterStorage::GetRawFilters() const
{
    return raw_filters_;
}

const Filters&FilterStorage::GetIPFilters() const
{
    return ip_filters_;
}

const Filters&FilterStorage::GetProtocolFilters(quint8 protocol) const
{
    return protocol_to_filters_[protocol];
}
