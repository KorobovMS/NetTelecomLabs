#include "settings.h"

Settings::Settings() :
    settings_(tr("settings.ini"), QSettings::IniFormat)
{
}
