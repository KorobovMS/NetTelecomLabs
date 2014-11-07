#ifndef WRITERSSTORAGE_H
#define WRITERSSTORAGE_H

#include <QHash>
#include <QSharedPointer>

class QJsonArray;
class Writer;

typedef QSharedPointer<Writer> WriterPtr;

/**
 * @brief The WritersStorage class contains an array of writers.
 *        These writers are parsed from JSON array
 */
class WritersStorage
{
public:
    WritersStorage(const QJsonArray& array);
    void WriteString(const QString& name, const QString& str);
    void WriteBytes(const QString& name, const QByteArray& arr);

private:
    typedef QHash<QString, WriterPtr> WritersCollection;
    WritersCollection writers_;
};

#endif // WRITERSSTORAGE_H
