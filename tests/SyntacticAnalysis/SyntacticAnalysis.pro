#-------------------------------------------------
#
# Project created by QtCreator 2013-12-01T18:58:30
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_syntacticanalysistest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_syntacticanalysistest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"
include (../srcTests.pri)
include (../../general.pri)
