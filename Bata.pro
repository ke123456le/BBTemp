#-------------------------------------------------
#
# Project created by QtCreator 2016-03-25T17:28:10
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bata
TEMPLATE = app


SOURCES += main.cpp \
    apps/mainwindow.cpp \
    source/dbmanager.cpp \
    source/master.cpp

HEADERS  += \
    apps/mainwindow.h \
    source/dbmanager.h \
    source/master.h \
    extend/include/bata.h \
    extend/include/cBmp.h \
    extend/include/hwjpeg.h \
    extend/include/jconfig.h \
    extend/include/jerror.h \
    extend/include/jmorecfg.h \
    extend/include/jpeglib.h \
    extend/include/t9mb.h \
    extend/include/uCom.h \
    extend/include/uVideo.h \
    source/errorcode.h

FORMS    += \
    apps/mainwindow.ui

DISTFILES += \
    ReadMe/readme.txt \
    README.md

unix:!macx: LIBS += -L$$PWD/extend/libs/ -lBataFaceIris
unix:!macx: LIBS += -L$$PWD/extend/libs/ -lhwjpeg
unix:!macx: LIBS += -L$$PWD/extend/libs/ -ljpeg
unix:!macx: LIBS += -L$$PWD/extend/libs/ -luVideo
unix:!macx: LIBS += -L$$PWD/extend/libs/ -lvpu

INCLUDEPATH += $$PWD/extend/libs
DEPENDPATH += $$PWD/extend/libs
