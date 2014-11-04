#include "filewriter.h"

FileWriter::FileWriter(const QString& path) :
    file_(path)
{
    if (file_.open(QIODevice::Append | QIODevice::Text))
    {
        stream_.setDevice(&file_);
    }
}

void FileWriter::Write(const QString& str)
{
    stream_ << str;
}
