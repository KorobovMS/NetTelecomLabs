#include "asciidataformatter.h"

AsciiDataFormatter::AsciiDataFormatter(const QByteArray& data)
{
    str_ = QString::fromLatin1(data);
    str_ += "\n";
}

const QString&AsciiDataFormatter::GetString() const
{
    return str_;
}
