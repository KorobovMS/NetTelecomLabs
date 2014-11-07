#include "asciidataformatter.h"

AsciiDataFormatter::AsciiDataFormatter(const QByteArray& data)
{
    SetData(data);
}

const QString&AsciiDataFormatter::GetString() const
{
    return str_;
}

void AsciiDataFormatter::SetData(const QByteArray& data)
{
    str_ = QString(data) + "\n";
}
