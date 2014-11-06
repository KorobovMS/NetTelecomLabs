#include "writersstorage.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>

#include "writer.h"
#include "filewriter.h"
#include "stdoutwriter.h"
#include "jsonutils.h"
#include "hexdataformatter.h"
#include "asciidataformatter.h"

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

        QString format_string;
        if (!GetJSONString(writer, "format", format_string))
        {
            format_string = "hex";
        }
        ByteArrayFormatterPtr fmt;
        if (format_string == "ascii")
        {
            fmt = ByteArrayFormatterPtr(new AsciiDataFormatter);
        }
        else
        {
            fmt = ByteArrayFormatterPtr(new HexDataFormatter);
        }


        if (type == "stdout")
        {
            writers_.insert(name, WriterPtr(new StdoutWriter(fmt)));
        }
        else if (type == "file")
        {
            QString filename;
            if (!GetJSONString(writer, "filename", filename))
            {
                continue;
            }

            writers_.insert(name, WriterPtr(new FileWriter(filename, fmt)));
        }
    }
}

void WritersStorage::WriteString(const QString& name, const QString& str)
{
    WritersCollection::iterator it = writers_.find(name);
    if (it != writers_.end())
    {
        it.value()->WriteString(str);
    }
}

void WritersStorage::WriteBytes(const QString& name, const QByteArray& arr)
{
    WritersCollection::iterator it = writers_.find(name);
    if (it != writers_.end())
    {
        it.value()->WriteBytes(arr);
    }
}
