#ifndef FILTER_H
#define FILTER_H

#include <QHostAddress>
#include <QString>

#include "ippacket.h"

/**
 * @brief The Filter class is responsible for IP packet filtering by
 *        source and destination addresses. It has a link to Writer class,
 *        which is available through GetWriter.
 *        User can set addresses, writer and the ability to successfully
 *        filter raw data.
 */
class Filter
{
public:
    Filter();

    bool Apply(const IPPacket& packet) const;
    bool IsRawApplied() const;
    const QString& GetWriter() const;

    void SetFrom(const QHostAddress& from);
    void SetTo(const QHostAddress& to);
    void SetRawFormat();
    void SetWriter(const QString& writer);

private:
    QHostAddress from_;
    QHostAddress to_;
    QString writer_;
    bool is_raw_applied_;
};

#endif // FILTER_H
