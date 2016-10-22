#ifndef SCENE_H
#define SCENE_H

#include "raster.h"
#include "tool.h"
#include "drawable.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QList>

class Tool;

class Scene : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    Scene(QWidget *parent = nullptr);
    ~Scene();
    Raster& raster()
        { return *rst; }

    quint32 foregroundColor();
    void setForegroundColor(quint32 color);
    quint32 backgroundColor();
    void setBackgroundColor(quint32 color);

    void addObject(Drawable *obj);

signals:
    void objectAdded(Drawable *obj);
    void objectSelected(int idx);

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Raster *rst;
    quint32 forecol;
    quint32 backcol;
    Tool *tool;
    QList<Drawable*> objects;
    Drawable *draggingObj;
    QPoint draggingPos;
};

inline quint32 Scene::foregroundColor()
{
    return forecol;
}

inline void Scene::setForegroundColor(quint32 color)
{
    forecol = color;
}

inline quint32 Scene::backgroundColor()
{
    return backcol;
}

inline void Scene::setBackgroundColor(quint32 color)
{
    backcol = color;
    update();
}

#endif // SCENE_H
