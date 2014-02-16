#-------------------------------------------------
#
# Project created by QtCreator 2013-11-23T19:37:15
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_smarttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_smarttest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
include (../srcTests.pri)
