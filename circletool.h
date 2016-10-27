#ifndef CIRCLETOOL_H
#define CIRCLETOOL_H

#include "tool.h"
#include "circle.h"

class CircleTool : public Tool
{
public:
    CircleTool(Scene &scene) : Tool(scene) {}

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

protected:
    Circle *circle;
};

#endif // CIRCLETOOL_H
