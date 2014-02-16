QT      += core sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kernel
TEMPLATE = lib
CONFIG += staticlib c++11

HEADERS += \
    inoffer.h \
    morphologicalanalysis.h \
    morphostructure.h \
    syntacticanalysis.h \
    SyntacticRuleStructure.h

SOURCES += \
    inoffer.cpp \
    morphologicalanalysis.cpp \
    syntacticanalysis.cpp
