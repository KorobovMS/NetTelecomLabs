#ifndef FILTER_H
#define FILTER_H

#include <QHostAddress>
#include <QJsonArray>
#include <QJsonObject>
#include <QObject>
#include <QSet>
#include <QString>

class Filter : public QObject
{
    Q_OBJECT

public:
    explicit Filter(const QJsonObject& obj, QObject* parent = 0);

private:
    typedef QSet<QString> Protocols;
    typedef QSet<QHostAddress> Addresses;

    void StringsToSet(const QJsonArray& array, Protocols& set);
    void HostsToSet(const QJsonArray& array, Addresses& set);

    QString id_;
    Protocols protocols_;
    Addresses from_;
    Addresses to_;
};

#endif // FILTER_H
