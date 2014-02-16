#-------------------------------------------------
#
# Project created by QtCreator 2013-11-23T20:48:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gui
TEMPLATE = lib
CONFIG += staticlib


SOURCES += main.cpp\
        lingagui.cpp

HEADERS  += lingagui.h \
    main.h

FORMS    += lingagui.ui

LIBS += -L$$OUT_PWD/../kernel/ -lkernel

INCLUDEPATH += $$PWD/../kernel
DEPENDPATH += $$PWD/../kernel

PRE_TARGETDEPS += $$OUT_PWD/../kernel/libkernel.a
