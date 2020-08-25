TEMPLATE      = lib
CONFIG       += plugin
QT           += widgets
QT           += xml
QT           += core gui
QT           += xlsx
TARGET        = $$qtLibraryTarget(gdut_fsae)
DESTDIR       = ./plugin


CONFIG(debug, debug|release){
LIBS += -L$$PWD/sdk/ -lqucd
} else {
LIBS += -L$$PWD/sdk/ -lquc
}

INCLUDEPATH += \
    inc\
    sdk\

HEADERS += \
    inc\gdut_fsae_plugin.h \
    inc\gdut_fsae_interface.h \
    inc\mainwindow.h\
    sdk\wavechart.h \
    sdk\navlabel.h \
    sdk\gaugewatch.h\
    sdk\gaugepanel.h

FORMS += \
    ui\mainwindow.ui

SOURCES += \
    src\gdut_fsae_plugin.cpp \
    src\mainwindow.cpp

RESOURCES += \
    gdut_fsae.qrc
