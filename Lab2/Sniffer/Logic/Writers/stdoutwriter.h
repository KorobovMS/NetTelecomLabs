#ifndef STDOUTWRITER_H
#define STDOUTWRITER_H

#include <QTextStream>
#include "writer.h"

/**
 * @brief The StdoutWriter class writes string to stdout
 */
class StdoutWriter : public Writer
{
public:
    StdoutWriter();
    virtual void Write(const QString& str);

private:
    QTextStream stdout_;
};

#endif // STDOUTWRITER_H
