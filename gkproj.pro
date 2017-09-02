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
    griddialog.cpp \
    filldialog.cpp \
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
    tools/smoothcircletool.cpp \
    widgets/coloredit.cpp \
    widgets/filterwidget.cpp \
    widgets/functionwidget.cpp \
    widgets/histogramchannelwidget.cpp \
    widgets/histogramwidget.cpp \
    widgets/scene.cpp \
    models/clipwindow.cpp \
    models/function.cpp \
    models/grid.cpp \
    models/matrix.cpp \
    models/octree.cpp \
    models/window.cpp

HEADERS += \
    mainwindow.h \
    griddialog.h \
    dist.h \
    filldialog.h \
    assert.h \
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
    tools/tool.h \
    widgets/coloredit.h \
    widgets/filterwidget.h \
    widgets/functionwidget.h \
    widgets/histogramchannelwidget.h \
    widgets/histogramwidget.h \
    widgets/scene.h \
    models/clipwindow.h \
    models/function.h \
    models/grid.h \
    models/matrix.h \
    models/octree.h \
    models/raster.h \
    models/window.h

FORMS += \
    mainwindow.ui \
    griddialog.ui \
    filldialog.ui \
    widgets/coloredit.ui \
    widgets/filterwidget.ui
