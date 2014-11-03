INCLUDEPATH += \
    $$PWD/Filter \
    $$PWD/Listener \
    $$PWD/Headers

HEADERS += \
    $$PWD/Filter/filter.h \
    $$PWD/Listener/listener.h \
    $$PWD/Headers/ipheader.h \
    $$PWD/Headers/tcpheader.h \
    $$PWD/Headers/udpheader.h \
    $$PWD/headers/icmpheader.h

SOURCES += \
    $$PWD/Filter/filter.cpp \
    $$PWD/Listener/listener.cpp
