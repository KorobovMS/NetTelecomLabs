#-------------------------------------------------
#
# Project created by QtCreator 2014-09-17T22:55:16
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    senddialog.cpp \
    sendprogressdialog.cpp \
    recieveprogressdialog.cpp \
    configdialog.cpp \
    reqtodldialog.cpp \
    sendtransaction.cpp \
    message.cpp \
    receivetransaction.cpp

HEADERS  += mainwindow.h \
    senddialog.h \
    sendprogressdialog.h \
    recieveprogressdialog.h \
    configdialog.h \
    reqtodldialog.h \
    sendtransaction.h \
    message.h \
    helpers.h \
    receivetransaction.h

FORMS    += mainwindow.ui \
    senddialog.ui \
    sendprogressdialog.ui \
    recieveprogressdialog.ui \
    configdialog.ui \
    reqtodldialog.ui
