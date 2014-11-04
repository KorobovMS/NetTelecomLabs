#include "datagramprocessor.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>

#include "writersstorage.h"
#include "filterstorage.h"
#include "hexdataformatter.h"
#include "ipheaderformatter.h"
#include "icmpheaderformatter.h"
#include "udpheaderformatter.h"
#include "tcpheaderformatter.h"
#include "asciidataformatter.h"
#include "ippacket.h"
#include "parsers.h"

DatagramProcessor::DatagramProcessor() :
    writers_(0),
    filters_(0)
{
    QFile file("settings.json");
    if (file.open(QIODevice::ReadOnly))
    {
        QJsonParseError error;
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);
        if (error.error == QJsonParseError::NoError)
        {
            QJsonObject settings = doc.object();
            writers_ = new WritersStorage(settings["writers"].toArray());
            filters_ = new FilterStorage(settings["filters"].toArray());
        }
    }
}

void DatagramProcessor::Process(const QByteArray& datagram)
{
    if (writers_ == 0 || filters_ == 0)
    {
        qDebug() << "Writers or filters are nullptr";
        return;
    }

    const Filters& raw_filters = filters_->GetRawFilters();
    if (raw_filters.size() != 0)
    {
        HexDataFormatter formatter(datagram);
        Filters::const_iterator it = raw_filters.begin();
        for (; it != raw_filters.end(); ++it)
        {
            if (it->IsRawApplied())
            {
                writers_->Write(it->GetWriter(), formatter.GetString() + "\n");
            }
        }
    }

    IPPacket ip = ParseIP(datagram);
    IPHeaderFormatter ip_formatter(ip);
    QString ip_header = ip_formatter.GetString();
    const Filters& ip_filters = filters_->GetIPFilters();
    if (ip_filters.size() != 0)
    {
        HexDataFormatter ip_data_formatter(ip.data);
        QString to_file = ip_header + ip_data_formatter.GetString() + "\n";
        Filters::const_iterator it = ip_filters.begin();
        for (; it != ip_filters.end(); ++it)
        {
            if (it->Apply(ip))
            {
                writers_->Write(it->GetWriter(), to_file);
            }
        }
    }

    const Filters& protocol_filters = filters_->GetProtocolFilters(ip.proto);
    QString to_file = ip_header;
    switch (ip.proto)
    {
    case Protocols::ICMP:
    {
        ICMPSegment icmp = ParseICMP(ip.data);
        ICMPHeaderFormatter hf(icmp);
        HexDataFormatter df(icmp.data);
        to_file += hf.GetString();
        to_file += df.GetString();
        to_file += "\n";
        break;
    }

    case Protocols::TCP:
    {
        TCPSegment tcp = ParseTCP(ip.data);
        TCPHeaderFormatter hf(tcp);
        AsciiDataFormatter df(tcp.data);
        to_file += hf.GetString();
        to_file += df.GetString();
        to_file += "\n";
        break;
    }

    case Protocols::UDP:
    {
        UDPSegment udp = ParseUDP(ip.data);
        UDPHeaderFormatter hf(udp);
        HexDataFormatter df(udp.data);
        to_file += hf.GetString();
        to_file += df.GetString();
        to_file += "\n";
        break;
    }
    }
    if (protocol_filters.size() != 0)
    {
        Filters::const_iterator it = protocol_filters.begin();
        for (; it != protocol_filters.end(); ++it)
        {
            if (it->Apply(ip))
            {
                writers_->Write(it->GetWriter(), to_file);
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
