#ifndef EMAIL_H
#define EMAIL_H

#include <QHash>
#include <QString>

typedef QHash<QString, QString> Headers;

struct Email
{
    Email(int n, const Headers& h, const QString& b);
    int number;
    Headers headers;
    QString body;
};

#endif // EMAIL_H
