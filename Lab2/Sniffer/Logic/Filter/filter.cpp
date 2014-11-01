#include "filter.h"

#include <QJsonValue>

Filter::Filter(const QJsonObject& obj, QObject* parent) :
    QObject(parent)
{
    id_ = obj["name"];
    StringsToSet(obj["protocols"].toArray(), protocols_);
    HostsToSet(obj["from"].toArray(), from_);
    HostsToSet(obj["to"].toArray(), to_);
}

void Filter::StringsToSet(const QJsonArray& array, Protocols& set)
{
    for (QJsonArray::const_iterator i = array.begin(); i != array.end(); ++i)
    {
        set.insert((*i).toString());
    }
}

void Filter::HostsToSet(const QJsonArray& array, Addresses& set)
{
    for (QJsonArray::const_iterator i = array.begin(); i != array.end(); ++i)
    {
        set.insert(QHostAddress((*i).toString()));
    }
}
