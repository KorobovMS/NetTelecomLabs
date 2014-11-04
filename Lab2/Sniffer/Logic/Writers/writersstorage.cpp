#include "writersstorage.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

#include "writer.h"
#include "filewriter.h"
#include "stdoutwriter.h"
#include "jsonutils.h"

WritersStorage::WritersStorage(const QJsonArray& array)
{
    QJsonArray::const_iterator it = array.begin();
    for (; it != array.end(); ++it)
    {
        QJsonObject writer = (*it).toObject();

        QString name;
        if (!GetJSONString(writer, "name", name))
        {
            continue;
        }

        QString type;
        if (!GetJSONString(writer, "type", type))
        {
            continue;
        }

        if (type == "stdout")
        {
            writers_.insert(name, WriterPtr(new StdoutWriter));
        }
        else if (type == "file")
        {
            QString filename;
            if (!GetJSONString(writer, "filename", filename))
            {
                continue;
            }

            writers_.insert(name, WriterPtr(new FileWriter(filename)));
        }
    }
}

void WritersStorage::Write(const QString& name, const QString& str)
{
    WritersCollection::iterator it = writers_.find(name);
    if (it != writers_.end())
    {
        it.value()->Write(str);
    }
}
