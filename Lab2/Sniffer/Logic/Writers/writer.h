#ifndef WRITER_H
#define WRITER_H

#include <QString>

class Writer
{
public:
    virtual void Write(const QString& str) = 0;
    virtual ~Writer() {}
};

#endif // WRITER_H
