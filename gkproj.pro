#-------------------------------------------------
#
# Project created by QtCreator 2016-10-09T09:58:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gkproj
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    line.cpp \
    grid.cpp \
    circle.cpp \
    griddialog.cpp \
    scene.cpp \
    circletool.cpp \
    point.cpp \
    pointtool.cpp \
    linetool.cpp \
    movetool.cpp \
    coloredit.cpp \
    smoothcircle.cpp \
    smoothcircletool.cpp \
    polygon.cpp \
    polygontool.cpp \
    filltool.cpp \
    fill.cpp \
    clipwindow.cpp

HEADERS  += mainwindow.h \
    raster.h \
    line.h \
    grid.h \
    circle.h \
    drawable.h \
    griddialog.h \
    scene.h \
    tool.h \
    circletool.h \
    dist.h \
    point.h \
    pointtool.h \
    linetool.h \
    movetool.h \
    coloredit.h \
    smoothcircle.h \
    smoothcircletool.h \
    polygon.h \
    polygontool.h \
    filltool.h \
    fill.h \
    clipwindow.h

FORMS    += mainwindow.ui \
    griddialog.ui \
    coloredit.ui
