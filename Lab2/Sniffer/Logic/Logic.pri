INCLUDEPATH += \
    $$PWD/Filter \
    $$PWD/Listener \
    $$PWD/Data \
    $$PWD/Parsers \
    $$PWD/Formatter \
    $$PWD/Writers \
    $$PWD/JSONUtils

HEADERS += \
    $$PWD/Filter/filter.h \
    $$PWD/Listener/listener.h \
    $$PWD/Parsers/parsers.h \
    $$PWD/Data/ippacket.h \
    $$PWD/Data/tcpsegment.h \
    $$PWD/Data/icmpsegment.h \
    $$PWD/Data/udpsegment.h \
    $$PWD/Formatter/formatter.h \
    $$PWD/Formatter/ipheaderformatter.h \
    $$PWD/Formatter/icmpheaderformatter.h \
    $$PWD/Formatter/udpheaderformatter.h \
    $$PWD/Formatter/tcpheaderformatter.h \
    $$PWD/Writers/writer.h \
    $$PWD/Writers/stdoutwriter.h \
    $$PWD/Writers/filewriter.h \
    $$PWD/Writers/writersstorage.h \
    $$PWD/Filter/filterstorage.h \
    $$PWD/JSONUtils/jsonutils.h \
    $$PWD/Formatter/hexdataformatter.h \
    $$PWD/Formatter/asciidataformatter.h \
    $$PWD/Writers/formattedwriter.h \
    $$PWD/Formatter/bytearrayformatter.h

SOURCES += \
    $$PWD/Filter/filter.cpp \
    $$PWD/Listener/listener.cpp \
    $$PWD/Parsers/parsers.cpp \
    $$PWD/Formatter/ipheaderformatter.cpp \
    $$PWD/Formatter/icmpheaderformatter.cpp \
    $$PWD/Formatter/udpheaderformatter.cpp \
    $$PWD/Formatter/tcpheaderformatter.cpp \
    $$PWD/Writers/stdoutwriter.cpp \
    $$PWD/Writers/filewriter.cpp \
    $$PWD/Writers/writersstorage.cpp \
    $$PWD/Filter/filterstorage.cpp \
    $$PWD/JSONUtils/jsonutils.cpp \
    $$PWD/Formatter/hexdataformatter.cpp \
    $$PWD/Formatter/asciidataformatter.cpp \
    $$PWD/Writers/formattedwriter.cpp
