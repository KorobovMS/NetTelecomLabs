#ifndef FILTERSTORAGE_H
#define FILTERSTORAGE_H

#include <QHash>
#include <QVector>

#include "filter.h"

class QJsonArray;
typedef QVector<Filter> Filters;

/**
 * @brief The FilterStorage class provides storage for next filters:
 *            1) raw data
 *            2) IP packets
 *            3) ICMP messages
 *            4) UDP datagrams
 *            5) TCP streams
 *        It parses JSON array in ctor to fill internal collections.
 */
class FilterStorage
{
public:
    FilterStorage(const QJsonArray& array);
    Filters GetRawFilters() const;
    Filters GetIPFilters() const;
    Filters GetProtocolFilters(quint8 protocol) const;

private:
    QHash<quint8, Filters> protocol_to_filters_;
    Filters raw_filters_;
    Filters ip_filters_;
};

#endif // FILTERSTORAGE_H
