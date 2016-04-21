#-------------------------------------------------
#
# Project created by QtCreator 2016-03-25T17:28:10
#
#-------------------------------------------------

QT       += core gui sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

target.path = /app/Bata
INSTALLS += target



TARGET = Bata
TEMPLATE = app

QTPLUGIN     += BataCameraPulgin


SOURCES += main.cpp \
    apps/mainwindow.cpp \
    source/dbmanager.cpp \
    source/master.cpp \
    source/logmanager.cpp \
    source/userftrmanager.cpp \
    source/systemconfig.cpp \
    source/devicemanager.cpp \
    source/identparamanager.cpp \
    source/orgmanager.cpp \
    source/usermanager.cpp \
    source/loadsplash.cpp \
    source/common/datetimewidget.cpp \
    apps/silenceinterface.cpp \
    apps/maininterface.cpp \
    source/featurematch.cpp \
    source/camera/bcamera.cpp \
    source/camera/bcameractrlinterface.cpp \
    source/camera/busbcameractrlinterface.cpp \
    source/camera/bcsicameractrlinterface.cpp \
    source/camera/decode.cpp \
    source/camera/bfaceshowcamera.cpp \
    source/camera/bfaceidentcamera.cpp \
    source/camera/birisidentcamera.cpp

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
    source/errorcode.h \
    source/logmanager.h \
    source/userftrmanager.h \
    source/systemconfig.h \
    source/devicemanager.h \
    source/identparamanager.h \
    source/orgmanager.h \
    source/usermanager.h \
    source/loadsplash.h \
    source/common/datetimewidget.h \
    apps/silenceinterface.h \
    apps/maininterface.h \
    source/featurematch.h \
    source/camera/bcamera.h \
    source/camera/bcameractrlinterface.h \
    source/camera/busbcameractrlinterface.h \
    source/camera/bcsicameractrlinterface.h \
    source/camera/decode.h \
    source/camera/bfaceshowcamera.h \
    source/camera/bfaceidentcamera.h \
    source/camera/birisidentcamera.h

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

RESOURCES += \
    res/res.qrc
