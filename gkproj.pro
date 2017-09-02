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
    coloredit.cpp \
    clipwindow.cpp \
    octree.cpp \
    filldialog.cpp \
    window.cpp \
    histogramwidget.cpp \
    histogramchannelwidget.cpp \
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
    drawables/smoothcircle.cpp \
    tools/circletool.cpp \
    tools/filltool.cpp \
    tools/linetool.cpp \
    tools/manipulatetool.cpp \
    tools/pointer.cpp \
    tools/pointtool.cpp \
    tools/polygontool.cpp \
    tools/smoothcircletool.cpp

HEADERS += \
    mainwindow.h \
    raster.h \
    grid.h \
    griddialog.h \
    scene.h \
    dist.h \
    coloredit.h \
    clipwindow.h \
    octree.h \
    filldialog.h \
    window.h \
    assert.h \
    histogramwidget.h \
    histogramchannelwidget.h \
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
    drawables/smoothcircle.h \
    tools/circletool.h \
    tools/filltool.h \
    tools/linetool.h \
    tools/manipulatetool.h \
    tools/pointer.h \
    tools/pointtool.h \
    tools/polygontool.h \
    tools/smoothcircletool.h \
    tools/tool.h

FORMS += \
    mainwindow.ui \
    griddialog.ui \
    coloredit.ui \
    filldialog.ui \
    filterwidget.ui
