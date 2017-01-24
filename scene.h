#ifndef SCENE_H
#define SCENE_H

#include "raster.h"
#include "grid.h"
#include "clipwindow.h"
#include "tool.h"
#include "drawable.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QList>
#include <QTimer>

class Tool;
class Drawable;

class Scene : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
    Q_PROPERTY(int fps READ fps NOTIFY fpsChanged)

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

    bool isClipWindowVisible() const
        { return _clipWindowVisible; }
    ClipWindow & clipWindow()
        { return _clipWindow; }
    void setClipWindow(const ClipWindow &clipWindow)
        { _clipWindow = clipWindow; }

    bool isFilterWindowVisible() const
        { return _filterWindowVisible; }
    Window & filterWindow()
        { return _filterWindow; }
    void setFilterWindow(const Window &filterWindow)
        { _filterWindow = filterWindow; }

    Tool * tool() const
        { return _tool; }
    void setTool(Tool *tool);

    const QList<Drawable *> & objects() const
        { return _objects; }
    int selection() const
        { return _selection; }
    Drawable * selectedObject() const
        { return _selection >= 0 ? _objects[_selection] : NULL; }
    void addObject(Drawable *obj);

    int fps() const
        { return _fps; }

public slots:
    void toggleGrid(bool visible);
    void toggleClipWindow(bool visible);
    void toggleFilterWindow(bool visible);
    void selectObject(int idx);
    void reorderObject(int idx);
    void moveToFront();
    void moveToBack();
    void deleteObject();
    void renameObject(const QString &name);
    void setObjectColor(const QColor &color);

signals:
    void objectAdded(Drawable *obj);
    void objectSelected(int idx);
    void objectReordered(int from, int to);
    void objectDeleted(int idx);
    void objectRenamed(int idx, const QString &name);
    void painted(Scene *scene);
    void fpsChanged(int fps);

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

private slots:
    void updateFps();

private:
    Raster *rst;
    quint32 forecol;
    quint32 backcol;
    bool _gridVisible;
    Grid _grid;
    bool _clipWindowVisible;
    ClipWindow _clipWindow;
    bool _filterWindowVisible;
    Window _filterWindow;
    Tool *_tool;
    QList<Drawable *> _objects;
    int _selection;
    int _fps;
    QTimer *timer;
    int counter;
};

#endif // SCENE_H
