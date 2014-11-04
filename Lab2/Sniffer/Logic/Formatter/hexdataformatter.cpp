#include "hexdataformatter.h"

#include <QTextStream>

HexDataFormatter::HexDataFormatter(const QByteArray& data)
{
    const int max_number_in_raw = 16;
    int number_in_raw = 0;
    QTextStream stream(&str_, QIODevice::WriteOnly);
    for (QByteArray::const_iterator it = data.begin(); it != data.end(); ++it)
    {
        stream << QString("%1 ").arg(*it);
        ++number_in_raw;
        if (number_in_raw == max_number_in_raw)
        {
            number_in_raw = 0;
            stream << "\n";
        }
    }
    stream.flush();
}

const QString&HexDataFormatter::GetString() const
{
    return str_;
}
