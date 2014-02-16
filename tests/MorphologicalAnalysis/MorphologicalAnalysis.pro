#-------------------------------------------------
#
# Project created by QtCreator 2013-11-27T21:40:24
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_morphologicalanalysistest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_morphologicalanalysistest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
include (../srcTests.pri)
include (../../general.pri)
