#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <QFile>
#include <QTextStream>
#include "writer.h"

class FileWriter : public Writer
{
public:
    FileWriter(const QString& path);
    virtual void Write(const QString& str);

private:
    QFile file_;
    QTextStream stream_;
};

#endif // FILEWRITER_H
