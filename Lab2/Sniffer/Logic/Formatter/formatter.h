#ifndef FORMATTER_H
#define FORMATTER_H

#include <QString>

/**
 * @brief The Formatter class is base class for formatting data
 */
class Formatter
{
public:
    virtual const QString& GetString() const = 0;
    virtual ~Formatter() {}
};

#endif // FORMATTER_H
