#ifndef WRITERSSTORAGE_H
#define WRITERSSTORAGE_H

#include <QHash>
#include <QSharedPointer>

class QJsonArray;
class Writer;

typedef QSharedPointer<Writer> WriterPtr;

class WritersStorage
{
public:
    WritersStorage(const QJsonArray& array);
    void Write(const QString& name, const QString& str);

private:
    typedef QHash<QString, WriterPtr> WritersCollection;
    WritersCollection writers_;
};

#endif // WRITERSSTORAGE_H