#-------------------------------------------------
#
# Project created by QtCreator 2017-10-29T16:36:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CG
TEMPLATE = app

INCLUDEPATH += $$PWD/Include

SOURCES += Src/Circle.cpp \
    Src/Line.cpp \
    Src/main.cpp \
    Src/mainwindow.cpp \
    Src/openglwindow.cpp

HEADERS  += Include/Circle.h \
    Include/common.h \
    Include/graph.h \
    Include/Line.h \
    Include/mainwindow.h \
    Include/openglwindow.h \
    Include/Point.h

FORMS    += mainwindow.ui