#include "hexdataformatter.h"

#include <QTextStream>

HexDataFormatter::HexDataFormatter(const QByteArray& data)
{
    SetData(data);
}

const QString&HexDataFormatter::GetString() const
{
    return str_;
}

void HexDataFormatter::SetData(const QByteArray& data)
{
    const int max_number_in_raw = 16;
    int number_in_raw = 0;
    str_.clear();
    QTextStream stream(&str_, QIODevice::WriteOnly);
    for (QByteArray::const_iterator it = data.begin(); it != data.end(); ++it)
    {
        stream << QString("%1 ")
                  .arg(static_cast<quint8>(*it), 2, 16, QChar('0'))
                  .toUpper();
        ++number_in_raw;
        if (number_in_raw == max_number_in_raw/2)
        {
            stream << "  ";
        }
        if (number_in_raw == max_number_in_raw)
        {
            number_in_raw = 0;
            stream << "\n";
        }
    }
    if (number_in_raw != 0)
    {
        stream << "\n";
    }
    stream.flush();
}
