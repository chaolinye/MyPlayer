#-------------------------------------------------
#
# Project created by QtCreator 2015-03-09T07:40:10
#
#-------------------------------------------------

QT       += core gui
QT       += webkit
QT       += webkitwidgets



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH += D:\MyPlayer\build-MyPlayer-Desktop_Qt_5_2_0_MinGW_32bit-Debug\debug\vlc
LIBS += D:\MyPlayer\build-MyPlayer-Desktop_Qt_5_2_0_MinGW_32bit-Debug\debug\lib\libvlc.lib
LIBS += D:\MyPlayer\build-MyPlayer-Desktop_Qt_5_2_0_MinGW_32bit-Debug\debug\lib\libvlccore.lib
QTPLUGIN += D:\MyPlayer\build-MyPlayer-Desktop_Qt_5_2_0_MinGW_32bit-Debug\debug\lib\plugins

TARGET = MyPlayer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    vediowidget.cpp \
    controlwidget.cpp \
    browserwidget.cpp \
    addressbar.cpp \
    mylistwidget.cpp \
    titlebar.cpp \
    SliderForVideo.cpp \
    searchwidget.cpp \
    bloomfilter.cpp \
    dealweb.cpp

HEADERS  += mainwindow.h \
    vediowidget.h \
    controlwidget.h \
    browserwidget.h \
    addressbar.h \
    mylistwidget.h \
    titlebar.h \
    SliderForVideo.h \
    searchwidget.h \
    bloomfilter.h \
    dealweb.h \
    BitContainer.h

RC_FILE  += myico.rc

RESOURCES += \
    images.qrc \
    sounds.qrc
