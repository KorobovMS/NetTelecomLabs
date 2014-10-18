#include "settings.h"

#include <limits>

#include <QDir>
#include <QSettings>

namespace
{
const QString IP("peer/ip");
const QString PORT("peer/port");

const QString DOWNLOADS("filesystem/downloads");

const QString UDP_MTU("protocol/udp_mtu");
const QString MAX_RETRANSMISSIONS("protocol/max_retransmissions");
const QString TIMEOUT_FOR_SENDING("protocol/timeout_for_sending");
const QString TIMEOUT_FOR_PERMISSION("protocol/timeout_for_permission");
}

Settings::Settings(bool track, QObject* parent) :
    QObject(parent),
    filename_("settings.ini"),
    is_tracking_(track)
{
    ReadSettings();
    if (is_tracking_)
    {
        fsw_.addPath(filename_);
        connect(&fsw_, SIGNAL(fileChanged(QString)),
                this, SLOT(ProcessFileChange(QString)));
    }
}

bool Settings::GetIP(QHostAddress& ip) const
{
    if (!settings_.contains(IP))
    {
        return false;
    }
    ip = QHostAddress(settings_.value(IP).toString());
    return !ip.isNull();
}

bool Settings::GetPort(quint16& port) const
{
    if (!settings_.contains(PORT))
    {
        return false;
    }
    int new_port = settings_.value(PORT, -1).toInt();
    if (new_port < 0 || new_port > std::numeric_limits<quint16>::max())
    {
        return false;
    }
    port = new_port;
    return true;
}

void Settings::GetDownloads(QString& downloads)
{
    if (!settings_.contains(DOWNLOADS))
    {
        downloads = tr("./");
        SafeSet(DOWNLOADS, downloads);
    }
    else
    {
        QString value = settings_.value(DOWNLOADS).toString();
        if (!QDir(value).exists())
        {
            downloads = tr("./");
            SafeSet(DOWNLOADS, downloads);
        }
        else
        {
            downloads = value;
        }
    }   
}

void Settings::GetUdpMTU(int& mtu)
{
    const int min_mtu = 512;
    if (!settings_.contains(UDP_MTU))
    {
        mtu = min_mtu;
        SafeSet(UDP_MTU, mtu);
    }
    else
    {
        int value = settings_.value(UDP_MTU).toInt();
        if (value < min_mtu)
        {
            mtu = min_mtu;
            SafeSet(UDP_MTU, mtu);
        }
        else
        {
            mtu = value;
        }
    }
}

void Settings::GetMaxRetransmissions(int& retransmissions)
{
    const int standard_value = 5;
    if (!settings_.contains(MAX_RETRANSMISSIONS))
    {
        retransmissions = standard_value;
        SafeSet(MAX_RETRANSMISSIONS, retransmissions);
    }
    else
    {
        int value = settings_.value(MAX_RETRANSMISSIONS).toInt();
        if (value <= 0)
        {
            retransmissions = standard_value;
            SafeSet(MAX_RETRANSMISSIONS, retransmissions);
        }
        else
        {
            retransmissions = value;
        }
    }
}

void Settings::GetTimeoutForSending(int& timeout)
{
    const int standard_value = 5000;
    if (!settings_.contains(TIMEOUT_FOR_SENDING))
    {
        timeout = standard_value;
        SafeSet(TIMEOUT_FOR_SENDING, timeout);
    }
    else
    {
        int value = settings_.value(TIMEOUT_FOR_SENDING).toInt();
        if (value <= 0)
        {
            timeout = standard_value;
            SafeSet(TIMEOUT_FOR_SENDING, timeout);
        }
        else
        {
            timeout = value;
        }
    }
}

void Settings::GetTimeoutForPermission(int& timeout)
{
    const int standard_value = 60000;
    if (!settings_.contains(TIMEOUT_FOR_PERMISSION))
    {
        timeout = standard_value;
        SafeSet(TIMEOUT_FOR_PERMISSION, timeout);
    }
    else
    {
        int value = settings_.value(TIMEOUT_FOR_PERMISSION).toInt();
        if (value <= 0)
        {
            timeout = standard_value;
            SafeSet(TIMEOUT_FOR_PERMISSION, timeout);
        }
        else
        {
            timeout = value;
        }
    }
}

void Settings::ProcessFileChange(QString)
{
    ReadSettings();
    emit SettingsChanged();
}

void Settings::ReadSettings()
{
    settings_.clear();

    QSettings settings(filename_, QSettings::IniFormat);
    QStringList keys = settings.allKeys();
    for (QStringList::iterator it = keys.begin(); it != keys.end(); ++it)
    {
        settings_.insert(*it, settings.value(*it));
    }
}

void Settings::SafeSet(const QString& key, const QVariant& value)
{
    if (is_tracking_)
    {
        disconnect(&fsw_, SIGNAL(fileChanged(QString)), 0, 0);
        fsw_.removePath(filename_);
    }

    QSettings settings(filename_, QSettings::IniFormat);
    settings.setValue(key, value);
    settings.sync();
    settings_.insert(key, value);

    if (is_tracking_)
    {
        fsw_.addPath(filename_);
        connect(&fsw_, SIGNAL(fileChanged(QString)),
                this, SLOT(ProcessFileChange(QString)));
    }
}
