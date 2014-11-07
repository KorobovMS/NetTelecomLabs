#ifndef WRITER_H
#define WRITER_H

#include <QByteArray>
#include <QString>

/**
 * @brief The Writer class is a base class for writing capability
 */
class Writer
{
public:
    virtual void WriteString(const QString& str) = 0;
    virtual void WriteBytes(const QByteArray& arr) = 0;
    virtual ~Writer() {}
};

#endif // WRITER_H
