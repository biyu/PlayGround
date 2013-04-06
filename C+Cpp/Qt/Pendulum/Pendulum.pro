# -------------------------------------------------
# Project created by QtCreator 2010-07-19T21:55:48
# -------------------------------------------------
QT += core \
    gui
TARGET = Pendulum
TEMPLATE = app
SOURCES += main.cpp \
    PendulumBall.cpp \
    Pendulum.cpp
HEADERS += PendulumBall.h \
    Pendulum.h

LIBS += -L"Box2D"
LIBS += -lBox2D

CONFIG += mobility
MOBILITY = 
symbian { 
    TARGET.UID3 = 0xed48203c
    
    # TARGET.CAPABILITY +=
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 \
        0x800000
}
