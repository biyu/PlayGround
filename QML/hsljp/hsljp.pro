# Add more folders to ship with the application, here

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

QT+= declarative
symbian:TARGET.UID3 = 0xE5848CA9

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp


OTHER_FILES += \
    qml/main.qml \
    hsljp.desktop \
    hsljp.svg \
    hsljp.png \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog \
    qml/QuickRoutePlanPage.qml \
    qml/DestinationPicker.qml \
    qml/StartPointPicker.qml \
    qml/Constants.js \
    qml/SelectButton.qml \
    qml/RouteResultPage.qml \
    qml/RouteResultList.qml \
    qml/Locator.qml \
    qml/Core.js \
    qml/CoreHelper.js \
    qml/RouteResultListLoader.js \
    qml/NewDestinationSheet.qml \
    qml/LineEdit.qml \
    qml/Switcher.qml \
    qml/NotifyBanner.qml \
    qml/Database.js \
    qml/LoadIndicator.qml \
    qml/StartPointSelectPage.qml

RESOURCES += \
    res.qrc

# Please do not modify the following two lines. Required for deployment.
include(deployment.pri)
qtcAddDeployment()

# enable booster
CONFIG += qdeclarative-boostable
QMAKE_CXXFLAGS += -fPIC -fvisibility=hidden -fvisibility-inlines-hidden
QMAKE_LFLAGS += -pie -rdynamic

unix:!symbian:!maemo5 {
    target.path = /opt/hsljp/bin
    INSTALLS += target
}

unix:!symbian:!maemo5 {
    target.path = /opt/hsljp/bin
    INSTALLS += target
}

unix:!symbian:!maemo5 {
    target.path = /opt/hsljp/bin
    INSTALLS += target
}

unix:!symbian:!maemo5 {
    target.path = /opt/hsljp/bin
    INSTALLS += target
}
