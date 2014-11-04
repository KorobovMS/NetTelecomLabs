#include "asciidataformatter.h"

AsciiDataFormatter::AsciiDataFormatter(const QByteArray& data) :
    str_(data)
{
}

const QString&AsciiDataFormatter::GetString() const
{
    return str_;
}
