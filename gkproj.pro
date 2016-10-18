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
    rasterwidget.cpp \
    line.cpp \
    grid.cpp \
    circle.cpp \
    scene.cpp \
    outlinelist.cpp \
    griddialog.cpp

HEADERS  += mainwindow.h \
    raster.h \
    rasterwidget.h \
    line.h \
    grid.h \
    circle.h \
    scene.h \
    drawable.h \
    outlinelist.h \
    griddialog.h

FORMS    += mainwindow.ui \
    griddialog.ui
