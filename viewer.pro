#-------------------------------------------------
#
# Project created by QtCreator 2018-12-05T18:24:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = viewer
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QTPLUGIN += qsqloci qgif
CONFIG += static

CONFIG += c++17

SOURCES += \
        main.cpp \
    src/editor.cpp \
    src/glob_state.cpp \
    src/point.cpp \
    src/line.cpp \
    src/plotter.cpp \
    src/renderarea.cpp

HEADERS += \
    inc/editor.h \
    inc/glob_state.h \
    inc/point.h \
    inc/line.h \
    inc/plotter.h \
    inc/renderarea.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    application.qrc

DISTFILES += \
    CMakeLists.txt
