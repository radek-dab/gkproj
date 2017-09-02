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
    grid.cpp \
    griddialog.cpp \
    scene.cpp \
    circletool.cpp \
    pointtool.cpp \
    linetool.cpp \
    coloredit.cpp \
    smoothcircletool.cpp \
    polygontool.cpp \
    filltool.cpp \
    clipwindow.cpp \
    octree.cpp \
    filldialog.cpp \
    window.cpp \
    pointer.cpp \
    histogramwidget.cpp \
    histogramchannelwidget.cpp \
    manipulatetool.cpp \
    filterwidget.cpp \
    matrix.cpp \
    functionwidget.cpp \
    function.cpp \
    filters/functionfilter.cpp \
    filters/histogramstretchingfilter.cpp \
    filters/matrixfilter.cpp \
    filters/rotationfilter.cpp \
    filters/scalingfilter.cpp \
    drawables/circle.cpp \
    drawables/fill.cpp \
    drawables/line.cpp \
    drawables/object3d.cpp \
    drawables/point.cpp \
    drawables/polygon.cpp \
    drawables/smoothcircle.cpp

HEADERS += \
    mainwindow.h \
    raster.h \
    grid.h \
    griddialog.h \
    scene.h \
    tool.h \
    circletool.h \
    dist.h \
    pointtool.h \
    linetool.h \
    coloredit.h \
    smoothcircletool.h \
    polygontool.h \
    filltool.h \
    clipwindow.h \
    octree.h \
    filldialog.h \
    window.h \
    pointer.h \
    assert.h \
    histogramwidget.h \
    histogramchannelwidget.h \
    manipulatetool.h \
    filterwidget.h \
    matrix.h \
    functionwidget.h \
    function.h \
    filters/filter.h \
    filters/functionfilter.h \
    filters/histogramstretchingfilter.h \
    filters/matrixfilter.h \
    filters/rotationfilter.h \
    filters/scalingfilter.h \
    drawables/circle.h \
    drawables/drawable.h \
    drawables/fill.h \
    drawables/line.h \
    drawables/object3d.h \
    drawables/point.h \
    drawables/polygon.h \
    drawables/smoothcircle.h

FORMS += \
    mainwindow.ui \
    griddialog.ui \
    coloredit.ui \
    filldialog.ui \
    filterwidget.ui
