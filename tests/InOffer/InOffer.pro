#-------------------------------------------------
#
# Project created by QtCreator 2013-11-26T13:34:36
#
#-------------------------------------------------

QT       += testlib

QT       -= gui



TARGET = tst_inoffertest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_inoffertest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
include (../srcTests.pri)
include (../../general.pri)
