INCLUDEPATH += \
    $$PWD/Filter \
    $$PWD/Listener \
    $$PWD/Data \
    $$PWD/Parsers

HEADERS += \
    $$PWD/Filter/filter.h \
    $$PWD/Listener/listener.h \
    $$PWD/Parsers/parsers.h \
    $$PWD/Data/ippacket.h \
    $$PWD/Data/tcpsegment.h \
    $$PWD/Data/icmpsegment.h \
    $$PWD/Data/udpsegment.h

SOURCES += \
    $$PWD/Filter/filter.cpp \
    $$PWD/Listener/listener.cpp \
    $$PWD/Parsers/parsers.cpp
