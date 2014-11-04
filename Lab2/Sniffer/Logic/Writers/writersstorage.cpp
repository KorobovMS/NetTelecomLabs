#include "writersstorage.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

#include "writer.h"
#include "filewriter.h"
#include "stdoutwriter.h"

WritersStorage::WritersStorage(const QJsonArray& array)
{
    QJsonArray::const_iterator it = array.begin();
    for (; it != array.end(); ++it)
    {
        QJsonObject writer = (*it).toObject();

        QJsonObject::const_iterator name_it = writer.find("name");
        if (name_it == writer.end())
        {
            continue;
        }
        QJsonValue name_value = name_it.value();
        if (!name_value.isString())
        {
            continue;
        }
        QString name = name_value.toString();

        QJsonObject::const_iterator type_it = writer.find("type");
        if (type_it == writer.end())
        {
            continue;
        }
        QJsonValue type_value = type_it.value();
        if (!type_value.isString())
        {
            continue;
        }
        QString type = type_value.toString();

        if (type == "stdout")
        {
            writers_.insert(name, WriterPtr(new StdoutWriter));
        }
        else if (type == "file")
        {
            QJsonObject::const_iterator filename_it = writer.find("filename");
            if (filename_it == writer.end())
            {
                continue;
            }
            QJsonValue filename_value = filename_it.value();
            if (!filename_value.isString())
            {
                continue;
            }
            QString filename = filename_value.toString();

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
