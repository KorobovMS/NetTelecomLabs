#include "stdoutwriter.h"

StdoutWriter::StdoutWriter(ByteArrayFormatterPtr fmt) :
    FormattedWriter(fmt),
    stdout_(stdout)
{}

void StdoutWriter::WriteString(const QString& str)
{
    stdout_ << str;
    stdout_.flush();
}
