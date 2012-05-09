#-------------------------------------------------
#
# Project created by QtCreator 2012-05-09T15:46:59
#
#-------------------------------------------------

QT       += core gui

TARGET = client
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x
DEFINES += CLIENT_MAIN

SOURCES += main.cpp\
        mainwindow.cpp \
    clientcontroller.cpp

HEADERS  += mainwindow.h \
    clientcontroller.h

FORMS    += mainwindow.ui

INCLUDEPATH += ../renderer/base \
               ../renderer/comm \
               ../renderer/math \
               ../renderer/rend \
               ../renderer/

LIBS += -L../renderer-debug/ -lrenderer
