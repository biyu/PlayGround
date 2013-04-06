#-------------------------------------------------
#
# Project created by QtCreator 2010-08-25T18:30:40
#
#-------------------------------------------------

QT       += core gui webkit network

TARGET = cumo
TEMPLATE = app

DEPENDPATH += .
INCLUDEPATH += .

SOURCES += main.cpp \
    CuMoGUI/CuMoWidget.cpp \
    CuMoGUI/CuMoButton.cpp \
    CuMoGUI/CuMoCoverFlowView.cpp \
    CuMoGUI/Flickable.cpp \
    CuMoGUI/CuMoCoverFlowItem.cpp \
    CuMoGUI/CuMoLogo.cpp \
    CuMoGUI/CuMoDialog.cpp \
    CuMoAppManager.cpp \
    CuMoWebCore/CuMoBackend.cpp \
    CuMoGUI/CuMoLoader.cpp \
    CuMoGUI/CuMoComboBox.cpp

HEADERS  += \
    CuMoGUI/CuMoWidget.h \
    CuMoGUI/CuMoButton.h \
    CuMoGUI/CuMoComboBox.h \
    CuMoGUI/CuMoLogo.h \
    CuMoGUI/CuMoTextLine.h \
    CuMoGUI/CuMoCoverFlowView.h \
    CuMoGUI/Flickable.h \
    CuMoGUI/CuMoCoverFlowItem.h \
    CuMoGUI/CuMoDialog.h \
    CuMoAppManager.h \
    CuMoWebCore/CuMoBackend.h \
    CuMoGUI/CuMoLoader.h \
    CuMoCommon.h

FORMS    +=

CONFIG += mobility
MOBILITY =

#CONFIG += link_pkgconfig
#PKGCONFIG += gq-gconf

symbian {
    TARGET.UID3 = 0xe87e8b90
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}

RESOURCES += \
    resources.qrc
