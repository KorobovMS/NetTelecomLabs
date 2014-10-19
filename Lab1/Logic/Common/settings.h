#ifndef SETTINGS_H
#define SETTINGS_H

#include <QFileSystemWatcher>
#include <QHash>
#include <QHostAddress>
#include <QObject>
#include <QString>
#include <QVariant>

class Settings : public QObject
{
    Q_OBJECT

public:
    Settings(bool track = true, QObject* parent = 0);

    void SetIP(const QHostAddress& addr);
    void SetPort(quint16 port);

    bool GetIP(QHostAddress& ip) const;
    bool GetPort(quint16& port) const;
    void GetDownloads(QString& downloads);
    void GetUdpMTU(int& mtu);
    void GetMaxRetransmissions(int& retransmissions);
    void GetTimeoutForSending(int& timeout);
    void GetTimeoutForPermission(int& timeout);

signals:
    void SettingsChanged();

private slots:
    void ProcessFileChange(QString);

private:
    void ReadSettings();
    void SafeSet(const QString& key, const QVariant& value);

private:
    const QString filename_;
    QHash<QString, QVariant> settings_;
    QFileSystemWatcher fsw_;
    bool is_tracking_;
};

#endif // SETTINGS_H
