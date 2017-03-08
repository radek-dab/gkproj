#-------------------------------------------------
#
# Project created by QtCreator 2016-10-09T09:58:04
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gkproj
TEMPLATE = app

CONFIG(debug, debug|release): DEFINES += \
    #DEBUG_EVENTS \
    #DEBUG_POLYGON \
    DEBUG_FILTERS \
    DEBUG_MATRIX \

SOURCES += \
    main.cpp \
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
    coloredit.cpp \
    smoothcircle.cpp \
    smoothcircletool.cpp \
    polygon.cpp \
    polygontool.cpp \
    filltool.cpp \
    fill.cpp \
    clipwindow.cpp \
    octree.cpp \
    filldialog.cpp \
    window.cpp \
    pointer.cpp \
    histogramwidget.cpp \
    histogramchannelwidget.cpp \
    object3d.cpp \
    manipulatetool.cpp \
    filterwidget.cpp \
    histogramstretchingfilter.cpp \
    scalingfilter.cpp \
    rotationfilter.cpp \
    matrixfilter.cpp \
    matrix.cpp

HEADERS += \
    mainwindow.h \
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
    coloredit.h \
    smoothcircle.h \
    smoothcircletool.h \
    polygon.h \
    polygontool.h \
    filltool.h \
    fill.h \
    clipwindow.h \
    octree.h \
    filldialog.h \
    window.h \
    pointer.h \
    assert.h \
    histogramwidget.h \
    histogramchannelwidget.h \
    object3d.h \
    manipulatetool.h \
    filterwidget.h \
    filter.h \
    histogramstretchingfilter.h \
    scalingfilter.h \
    rotationfilter.h \
    matrixfilter.h \
    matrix.h

FORMS += \
    mainwindow.ui \
    griddialog.ui \
    coloredit.ui \
    filldialog.ui \
    filterwidget.ui
