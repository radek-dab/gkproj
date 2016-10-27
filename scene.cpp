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
    _gridVisible(false),
    _grid(50, Raster::GREY),
    _tool(NULL),
    _selection(-1)
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
    selectObject(_objects.count()-1);
}

void Scene::toggleGrid(bool visible)
{
    _gridVisible = visible;
    update();
}

void Scene::selectObject(int idx)
{
    _selection = idx;
    emit objectSelected(idx);
}

void Scene::reorderObject(int idx)
{
    if (_selection == -1 || _selection == idx)
        return;

    _objects.move(_selection, idx);
    update();
    emit objectReordered(_selection, idx);

    selectObject(idx);
}

void Scene::moveToFront()
{
    reorderObject(_objects.count()-1);
}

void Scene::moveToBack()
{
    reorderObject(0);
}

void Scene::deleteObject()
{
    if (_selection == -1)
        return;

    Drawable *obj = _objects[_selection];
    _objects.removeAt(_selection);
    delete obj;
    update();
    emit objectDeleted(_selection);

    if (_selection == _objects.count())
        selectObject(_selection-1);
    else
        selectObject(_selection);
}

void Scene::renameObject(const QString &name)
{
    if (_selection != -1) {
        _objects[_selection]->setName(name);
        emit objectRenamed(_selection, name);
    }
}

void Scene::setObjectColor(const QColor &color)
{
    if (_selection != -1) {
        _objects[_selection]->setColor(color.rgba());
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
    if (_gridVisible)
        _grid.draw(*rst);
    foreach (Drawable *obj, _objects)
        obj->draw(*rst);

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
    _tool->mousePressEvent(event);
}

void Scene::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "Mouse move at" << event->pos();
    _tool->mouseMoveEvent(event);
}

void Scene::mouseReleaseEvent(QMouseEvent *event)
{
    _tool->mouseReleaseEvent(event);
}
