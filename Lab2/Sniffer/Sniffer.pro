#-------------------------------------------------
#
# Project created by QtCreator 2014-10-29T19:30:10
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = Sniffer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS += -lws2_32

include(Logic/Logic.pri)
include(Console/Console.pri)
