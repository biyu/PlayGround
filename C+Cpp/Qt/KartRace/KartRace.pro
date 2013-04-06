#-------------------------------------------------
#
# Project created by QtCreator 2010-07-26T23:31:28
#
#-------------------------------------------------

QT       += core gui

TARGET = KartRace
TEMPLATE = app


SOURCES += main.cpp \
    b2kart.cpp \
    b2worldview.cpp

HEADERS  += \
    b2kart.h \
    b2worldview.h

LIBS += -L"Box2D"
LIBS += -lBox2D

FORMS    +=

CONFIG += mobility
MOBILITY = 

RESOURCES +=
