#ifndef STDOUTWRITER_H
#define STDOUTWRITER_H

#include <QTextStream>
#include "formattedwriter.h"
#include "bytearrayformatter.h"

/**
 * @brief The StdoutWriter class writes string to stdout
 */
class StdoutWriter : public FormattedWriter
{
public:
    StdoutWriter(ByteArrayFormatterPtr fmt);
    virtual void WriteString(const QString& str);

private:
    QTextStream stdout_;
};

#endif // STDOUTWRITER_H
