#ifndef TOOL_H
#define TOOL_H

#include "scene.h"
#include <QMouseEvent>

class Scene;

class Tool
{
public:
    Tool(Scene &scene) : scene(scene) {}

    virtual void mousePressEvent(QMouseEvent *event) = 0;
    virtual void mouseMoveEvent(QMouseEvent *event) = 0;
    virtual void mouseReleaseEvent(QMouseEvent *event) = 0;

protected:
    Scene &scene;
};

#endif // TOOL_H
