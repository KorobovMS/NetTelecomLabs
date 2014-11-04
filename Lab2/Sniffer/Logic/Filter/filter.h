#ifndef FILTER_H
#define FILTER_H

#include <QHostAddress>
#include <QObject>
#include <QSet>
#include <QString>

#include "ippacket.h"

class Filter : public QObject
{
    Q_OBJECT

public:
    explicit Filter(QObject* parent = 0);

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
