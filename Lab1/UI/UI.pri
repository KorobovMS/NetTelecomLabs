INCLUDEPATH += \
    $$PWD/Configure \
    $$PWD/MainWindow \
    $$PWD/ReceiveProgress \
    $$PWD/ConfirmUpload \
    $$PWD/Send \
    $$PWD/SendProgress

FORMS += \
    $$PWD/Configure/configdialog.ui \
    $$PWD/MainWindow/mainwindow.ui \
    $$PWD/ReceiveProgress/receiveprogressdialog.ui \
    $$PWD/Send/senddialog.ui \
    $$PWD/SendProgress/sendprogressdialog.ui \
    $$PWD/ConfirmUpload/confirmuploaddialog.ui

HEADERS += \
    $$PWD/Configure/configdialog.h \
    $$PWD/MainWindow/mainwindow.h \
    $$PWD/ReceiveProgress/receiveprogressdialog.h \
    $$PWD/Send/senddialog.h \
    $$PWD/SendProgress/sendprogressdialog.h \
    $$PWD/ConfirmUpload/confirmuploaddialog.h

SOURCES += \
    $$PWD/Configure/configdialog.cpp \
    $$PWD/MainWindow/mainwindow.cpp \
    $$PWD/ReceiveProgress/receiveprogressdialog.cpp \
    $$PWD/Send/senddialog.cpp \
    $$PWD/SendProgress/sendprogressdialog.cpp \
    $$PWD/ConfirmUpload/confirmuploaddialog.cpp
