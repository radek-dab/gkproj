#include "scene.h"
#include "grid.h"
#include "line.h"
#include "circletool.h"
#include "pointtool.h"
#include "linetool.h"
#include <QDebug>
#include <QElapsedTimer>

Scene::Scene(QWidget *parent) :
    QOpenGLWidget(parent),
    rst(NULL),
    forecol(Raster::RED),
    backcol(Raster::BLACK),
    _grid(QSize(20, 20)),
    _tool(NULL),
    draggingObj(NULL)
{}

Scene::~Scene()
{
    if (rst)
        delete rst;
    if (_tool)
        delete _tool;
    foreach (Drawable *obj, _objects)
        delete obj;
}

void Scene::setTool(Tool *tool)
{
    if (_tool)
        delete _tool;
    _tool = tool;
}

void Scene::addObject(Drawable *obj)
{
    _objects.push_back(obj);
    update();
    emit objectAdded(obj);
    selectObject(_objects.length()-1);
}

void Scene::selectObject(int idx)
{
    if (_selection != idx) {
        _selection = idx;
        emit objectSelected(idx);
    }
}

void Scene::initializeGL()
{
    initializeOpenGLFunctions();
    glLoadIdentity();
}

void Scene::resizeGL(int width, int height)
{
    if (rst) delete rst;
    rst = new Raster(width, height/*, Raster::WHITE*/);
}

void Scene::paintGL()
{
    QElapsedTimer timer;
    timer.start();

    rst->clear(backcol);
    _grid.draw(*rst);
    foreach (Drawable *obj, _objects) {
        obj->draw(*rst);
    }

    quint64 drawing = timer.nsecsElapsed();
    timer.start();

    glPixelZoom(1, -1);     // Can it be moved into initializeGL?
    glRasterPos2f(-1, 1);   // This as well.
    glDrawPixels(rst->w, rst->h, GL_BGRA, GL_UNSIGNED_BYTE, rst->pixels());

    quint64 copying = timer.nsecsElapsed();
    qDebug() << "paintGL:" << qSetRealNumberPrecision(3)
             << "drawing" << drawing/1e6 << "ms +"
             << "copying" << copying/1e6 << "ms ="
             << (drawing+copying)/1e6 << "ms";
}

void Scene::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "Mouse clicked at" << event->pos();
    for (int i = 0; i < _objects.count(); i++) {
        Drawable *obj = _objects[i];
        if (obj->hit(event->pos())) {
            qDebug() << "Dragging" << obj;
            draggingObj = obj;
            draggingPos = event->pos();
            emit objectSelected(i);
            return;
        }
    }
    _tool->mousePressEvent(event);
}

void Scene::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "Mouse move at" << event->pos();
    if (draggingObj) {
        draggingObj->move(event->pos() - draggingPos);
        draggingPos = event->pos();
    } else {
        _tool->mouseMoveEvent(event);
    }
    update();
}

void Scene::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    draggingObj = NULL;
    _tool->mouseReleaseEvent(event);
}
