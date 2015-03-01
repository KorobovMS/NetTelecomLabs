#-------------------------------------------------
#
# Project created by QtCreator 2014-11-20T22:08:01
#
#-------------------------------------------------

QT       += core network gui widgets

TARGET = FTPClient
TEMPLATE = app

SOURCES += main.cpp\
    ftp.cpp \
    filebrowser.cpp \
    historywindow.cpp \
    loginwindow.cpp \
    filetransfer.cpp

HEADERS  += \
    ftp.h \
    filebrowser.h \
    historywindow.h \
    loginwindow.h \
    filetransfer.h

FORMS += \
    filebrowser.ui \
    historywindow.ui \
    loginwindow.ui
