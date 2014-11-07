#include "datagramprocessor.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

#include "writersstorage.h"
#include "filterstorage.h"
#include "ipheaderformatter.h"
#include "icmpheaderformatter.h"
#include "udpheaderformatter.h"
#include "tcpheaderformatter.h"
#include "ippacket.h"
#include "parsers.h"

DatagramProcessor::DatagramProcessor() :
    is_initialized_(false),
    writers_(0),
    filters_(0)
{}

bool DatagramProcessor::Initialize(const QString& settings_file)
{
    if (is_initialized_)
    {
        return is_initialized_;
    }

    QFile file(settings_file);
    if (file.open(QIODevice::ReadOnly))
    {
        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);
        if (error.error == QJsonParseError::NoError)
        {
            QJsonObject settings = doc.object();
            writers_ = new WritersStorage(settings["writers"].toArray());
            filters_ = new FilterStorage(settings["filters"].toArray());
            is_initialized_ = true;
        }
    }
    return is_initialized_;
}

void DatagramProcessor::Process(const QByteArray& datagram)
{
    if (!is_initialized_)
    {
        qDebug() << "Datagram processor is not initialized correctly";
        return;
    }

    const Filters& raw_filters = filters_->GetRawFilters();
    if (raw_filters.size() != 0)
    {
        Filters::const_iterator it = raw_filters.begin();
        for (; it != raw_filters.end(); ++it)
        {
            if (it->IsRawApplied())
            {
                writers_->WriteBytes(it->GetWriter(), datagram);
                writers_->WriteString(it->GetWriter(), "\n");
            }
        }
    }

    IPPacket ip = ParseIP(datagram);
    IPHeaderFormatter ip_formatter(ip);
    QString ip_header = ip_formatter.GetString();
    const Filters& ip_filters = filters_->GetIPFilters();
    if (ip_filters.size() != 0)
    {
        Filters::const_iterator it = ip_filters.begin();
        for (; it != ip_filters.end(); ++it)
        {
            if (it->Apply(ip))
            {
                writers_->WriteString(it->GetWriter(), ip_header);
                writers_->WriteBytes(it->GetWriter(), ip.data);
                writers_->WriteString(it->GetWriter(), "\n");
            }
        }
    }

    const Filters& protocol_filters = filters_->GetProtocolFilters(ip.proto);
    QString proto_header;
    QByteArray proto_data;
    switch (ip.proto)
    {
    case Protocols::ICMP:
    {
        ICMPSegment icmp = ParseICMP(ip.data);
        ICMPHeaderFormatter hf(icmp);
        proto_header = hf.GetString();
        proto_data = icmp.data;
        break;
    }

    case Protocols::TCP:
    {
        TCPSegment tcp = ParseTCP(ip.data);
        TCPHeaderFormatter hf(tcp);
        proto_header = hf.GetString();
        proto_data = tcp.data;
        break;
    }

    case Protocols::UDP:
    {
        UDPSegment udp = ParseUDP(ip.data);
        UDPHeaderFormatter hf(udp);
        proto_header = hf.GetString();
        proto_data = udp.data;
        break;
    }

    default:
        return;
    }

    if (protocol_filters.size() != 0)
    {
        Filters::const_iterator it = protocol_filters.begin();
        for (; it != protocol_filters.end(); ++it)
        {
            if (it->Apply(ip))
            {
                writers_->WriteString(it->GetWriter(), ip_header);
                writers_->WriteString(it->GetWriter(), proto_header);
                writers_->WriteBytes(it->GetWriter(), proto_data);
                writers_->WriteString(it->GetWriter(), "\n");
            }
        }
    }
}

DatagramProcessor::~DatagramProcessor()
{
    if (writers_ != 0)
    {
        delete writers_;
    }

    if (filters_ != 0)
    {
        delete filters_;
    }
}
