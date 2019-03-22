#-------------------------------------------------
#
# Project created by QtCreator 2018-11-23T11:36:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Str_Zone
TEMPLATE = app



SOURCES += main.cpp\
        mainwindow.cpp \
    colordetector.cpp \
    colordetectcontroller.cpp \
    histog1d.cpp \
    buscadcont.cpp \
    imagecomparator.cpp \
    morphofeatures.cpp \
    segmentadorws.cpp \
    laplacianzc.cpp \
    buscalinea.cpp \
    vibe.cpp

HEADERS  += mainwindow.h \
    colordetector.h \
    colordetectcontroller.h \
    histog1d.h \
    buscadcont.h \
    imagecomparator.h \
    morphofeatures.h \
    segmentadorws.h \
    laplacianzc.h \
    buscalinea.h \
    vibe.h

FORMS    += mainwindow.ui

CONFIG += link_pkgconfig


INCLUDEPATH += C:\Qt\Qt5.3.0\OpenCV-Compiled\include
LIBS += -LC:\Qt\Qt5.3.0\OpenCV-Compiled\lib-dll-Compiladas\bin \
-llibopencv_core246 \
-llibopencv_highgui246 \
-llibopencv_imgproc246 \
-llibopencv_features2d246 \
-llibopencv_calib3d246 \
-llibopencv_video246
