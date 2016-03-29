#-------------------------------------------------
#
# Project created by QtCreator 2016-03-25T17:28:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bata
TEMPLATE = app


SOURCES += main.cpp \
    apps/mainwindow.cpp

HEADERS  += \
    apps/mainwindow.h

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
