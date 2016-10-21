#include "scene.h"
#include "grid.h"
#include "line.h"
#include "circletool.h"
#include "pointtool.h"
#include <QDebug>
#include <QElapsedTimer>

Scene::Scene(QWidget *parent) :
    QOpenGLWidget(parent),
    rst(NULL),
    forecol(Raster::RED),
    backcol(Raster::BLACK),
    tool(new PointTool(*this)),
    draggingObj(NULL)
{}

Scene::~Scene()
{
    if (rst)
        delete rst;
    foreach (Drawable *obj, objects)
        delete obj;
}

void Scene::addObject(Drawable *obj)
{
    objects.push_back(obj);
    update();
    emit objectAdded(obj);
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
    foreach (Drawable *obj, objects) {
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
    for (int i = 0; i < objects.count(); i++) {
        Drawable *obj = objects[i];
        if (obj->hit(event->pos())) {
            qDebug() << "Dragging" << obj;
            draggingObj = obj;
            draggingPos = event->pos();
            emit objectSelected(i);
            return;
        }
    }
    tool->mousePressEvent(event);
}

void Scene::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "Mouse move at" << event->pos();
    if (draggingObj) {
        draggingObj->move(event->pos() - draggingPos);
        draggingPos = event->pos();
    } else {
        tool->mouseMoveEvent(event);
    }
    update();
}

void Scene::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    draggingObj = NULL;
    tool->mouseReleaseEvent(event);
}
