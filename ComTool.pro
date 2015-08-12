TEMPLATE = app

QT += qml quick widgets
QT += serialport

SOURCES += main.cpp \
    serialporthandler.cpp \
    portsdata.cpp \
    listmodel.cpp \
    emap.cpp

RESOURCES += qml.qrc \
    i18n.qrc \
    images.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    serialporthandler.h \
    portsdata.h \
    listmodel.h \
    emap.h

lupdate_only{
    SOURCES += qml/*.qml
}

TRANSLATIONS += i18n/comtool_zh_CN.ts

DISTFILES += \
    i18n/comtool_zh_CN.ts \
