#ifndef TOOL_H
#define TOOL_H

#include "widgets/scene.h"
#include <QMouseEvent>

class Scene;

class Tool
{
public:
    Tool(Scene &scene) : scene(scene) {}
    virtual ~Tool() {}

    virtual void mousePressEvent(QMouseEvent *event) = 0;
    virtual void mouseMoveEvent(QMouseEvent *event) = 0;
    virtual void mouseReleaseEvent(QMouseEvent *event) = 0;

    virtual void wheelEvent(QWheelEvent *event)
        { Q_UNUSED(event); } // By default do nothing

protected:
    Scene &scene;
};

#endif // TOOL_H
