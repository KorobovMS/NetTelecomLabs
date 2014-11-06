#include "filewriter.h"

FileWriter::FileWriter(const QString& path, ByteArrayFormatterPtr fmt) :
    FormattedWriter(fmt),
    file_(path)
{
    if (file_.open(QIODevice::Append | QIODevice::Text))
    {
        stream_.setDevice(&file_);
    }
}

void FileWriter::WriteString(const QString& str)
{
    stream_ << str;
}
