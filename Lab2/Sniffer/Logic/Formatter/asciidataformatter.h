#ifndef ASCIIDATAFORMATTER_H
#define ASCIIDATAFORMATTER_H

#include "formatter.h"

/**
 * @brief The AsciiDataFormatter class converts QByteArray to ascii string
 */
class AsciiDataFormatter : public Formatter
{
public:
    AsciiDataFormatter(const QByteArray& data);
    virtual const QString& GetString() const;

private:
    QString str_;
};

#endif // ASCIIDATAFORMATTER_H
