#include "formattedwriter.h"

FormattedWriter::FormattedWriter(ByteArrayFormatterPtr formatter) :
    formatter_(formatter)
{
}

void FormattedWriter::WriteBytes(const QByteArray& arr)
{
    formatter_->SetData(arr);
    WriteString(formatter_->GetString());
}
