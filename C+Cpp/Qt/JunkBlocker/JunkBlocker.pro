#-------------------------------------------------
#
# Project created by QtCreator 2010-08-30T17:55:19
#
#-------------------------------------------------

QT       += core gui

TARGET = JunkBlocker
TEMPLATE = app


SOURCES += main.cpp \
    JBlockerMainWindow.cpp \
    JBlockerCore.cpp \
    JBlockerMessageViewBox.cpp

HEADERS  += \
    JBlockerMainWindow.h \
    JBlockerCore.h \
    JBlockerMessageViewBox.h

FORMS    +=

CONFIG += mobility
MOBILITY = messaging contacts

symbian {
    TARGET.UID3 = 0xe2a00853
    # TARGET.CAPABILITY +=
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}
