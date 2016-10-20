#include "scene.h"
#include "grid.h"
#include "line.h"
#include "circle.h"
#include <cmath>
#include <QDebug>
#include <QElapsedTimer>

Scene::Scene(QWidget *parent) :
    QOpenGLWidget(parent),
    rst(NULL),
    foregroundColor(Raster::RED),
    backgroundColor(Raster::BLACK),
    inflatingObj(NULL),
    draggingObj(NULL)
{}

Scene::~Scene()
{
    if (rst)
        delete rst;
    foreach (Drawable *obj, objects)
        delete obj;
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

    rst->clear(backgroundColor);
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
    inflatingObj = new Circle(event->pos(), 0, foregroundColor);
    objects.push_back(inflatingObj);
    emit objectAdded(inflatingObj);
}

void Scene::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "Mouse move at" << event->pos();
    if (inflatingObj) {
        inflatingObj->inflate(event->pos());
    }
    if (draggingObj) {
        draggingObj->move(event->pos() - draggingPos);
        draggingPos = event->pos();
    }
    update();
}

void Scene::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    inflatingObj = NULL;
    draggingObj = NULL;
}
