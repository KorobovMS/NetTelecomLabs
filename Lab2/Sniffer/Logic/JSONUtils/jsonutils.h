#ifndef JSONUTILS_H
#define JSONUTILS_H

class QJsonObject;
class QString;

/**
 * @brief GetJSONString performs safe 'value = obj[key]'
 * @param obj JSON object
 * @param key Key of value we want to extract
 * @param value if obj[key] is string, then value is obj[key]
 * @return true if function succeedes
 */
bool GetJSONString(const QJsonObject& obj, const QString& key, QString& value);

#endif // JSONUTILS_H
