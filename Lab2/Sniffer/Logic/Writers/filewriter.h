#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <QFile>
#include <QTextStream>
#include "formattedwriter.h"

/**
 * @brief The FileWriter class writes string to file specified in ctor
 */
class FileWriter : public FormattedWriter
{
public:
    FileWriter(const QString& path, ByteArrayFormatterPtr fmt);
    virtual void WriteString(const QString& str);

private:
    QFile file_;
    QTextStream stream_;
};

#endif // FILEWRITER_H
