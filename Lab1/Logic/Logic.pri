INCLUDEPATH += \
    $$PWD/Common \
    $$PWD/Receiver \
    $$PWD/Sender

HEADERS += \
    $$PWD/Common/helpers.h \
    $$PWD/Common/message.h \
    $$PWD/Receiver/receivetransaction.h \
    $$PWD/Receiver/server.h \
    $$PWD/Sender/sendtransaction.h

SOURCES += \
    $$PWD/Common/message.cpp \
    $$PWD/Receiver/receivetransaction.cpp \
    $$PWD/Receiver/server.cpp \
    $$PWD/Sender/sendtransaction.cpp
