#ifndef JSONUTILS_H
#define JSONUTILS_H

class QJsonObject;
class QString;

bool GetJSONString(const QJsonObject& obj, const QString& key, QString& value);

#endif // JSONUTILS_H
