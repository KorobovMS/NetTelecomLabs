#include "jsonutils.h"

#include <QJsonObject>
#include <QJsonValue>

bool GetJSONString(const QJsonObject& obj, const QString& key, QString& value)
{
    QJsonObject::const_iterator iter = obj.find(key);
    if (iter == obj.end())
    {
        return false;
    }

    QJsonValue json_value = iter.value();
    if (!json_value.isString())
    {
        return false;
    }

    value = json_value.toString();
    return true;
}
