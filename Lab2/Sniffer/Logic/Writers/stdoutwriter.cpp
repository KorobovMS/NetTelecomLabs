#include "stdoutwriter.h"

StdoutWriter::StdoutWriter() :
    stdout_(stdout)
{

}

void StdoutWriter::Write(const QString& str)
{
    stdout_ << str;
    stdout_.flush();
}
