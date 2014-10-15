#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>

class Settings : public QObject
{
public:
    Settings();

private:
    QSettings settings_;
};

#endif // SETTINGS_H
