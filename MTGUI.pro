#-------------------------------------------------
#
# Project created by QtCreator 2016-12-06T18:54:54
#
#-------------------------------------------------

QT       += core gui
QT += printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MTGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    md5.c \
    mikrotik-api.c \
    configuration.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    md5.h \
    mikrotik-api.h \
    configuration.h

FORMS    += mainwindow.ui
