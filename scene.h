#ifndef SCENE_H
#define SCENE_H

#include "raster.h"
#include "grid.h"
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

    quint32 foregroundColor() const
        { return forecol; }
    void setForegroundColor(quint32 color)
        { forecol = color; }

    quint32 backgroundColor() const
        { return backcol; }
    void setBackgroundColor(quint32 color)
        { backcol = color; update(); }

    bool isGridVisible() const
        { return _gridVisible; }
    Grid grid() const
        { return _grid; }
    void setGrid(const Grid &grid)
        { _grid = grid; update(); }

    Tool * tool() const
        { return _tool; }
    void setTool(Tool *tool);

    const QList<Drawable *> objects() const
        { return _objects; }
    int selection() const
        { return _selection; }
    void addObject(Drawable *obj);

public slots:
    void toggleGrid(bool visible);
    void selectObject(int idx);
    void deleteObject();

signals:
    void objectAdded(Drawable *obj);
    void objectSelected(int idx);
    void objectDeleted(int idx);

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
    bool _gridVisible;
    Grid _grid;
    Tool *_tool;
    QList<Drawable *> _objects;
    int _selection;
};

#endif // SCENE_H
