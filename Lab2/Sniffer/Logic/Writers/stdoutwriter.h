#ifndef STDOUTWRITER_H
#define STDOUTWRITER_H

#include <QTextStream>
#include "writer.h"

class StdoutWriter : public Writer
{
public:
    StdoutWriter();
    virtual void Write(const QString& str);

private:
    QTextStream stdout_;
};

#endif // STDOUTWRITER_H
