QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = app
TEMPLATE = app


SOURCES += main.cpp


LIBS += -L$$OUT_PWD/../gui/ -lgui

INCLUDEPATH += $$PWD/../gui
DEPENDPATH += $$PWD/../gui

PRE_TARGETDEPS += $$OUT_PWD/../gui/libgui.a

LIBS += -L$$OUT_PWD/../kernel/ -lkernel

INCLUDEPATH += $$PWD/../kernel
DEPENDPATH += $$PWD/../kernel

PRE_TARGETDEPS += $$OUT_PWD/../kernel/libkernel.a
