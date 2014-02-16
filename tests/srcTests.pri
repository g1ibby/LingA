TEMPLATE = app
DEPENDPATH += . ../../kernel/
INCLUDEPATH += . ../../kernel/
DESTDIR = ./
CONFIG += qtestlib
CONFIG += testcase # IMPORTANT

#QMAKE_POST_LINK=./$$TARGET

LIBS += -L$$OUT_PWD/../../kernel/ -lkernel

INCLUDEPATH += $$PWD/../../kernel
DEPENDPATH += $$PWD/../../kernel

PRE_TARGETDEPS += $$OUT_PWD/../../kernel/libkernel.a
