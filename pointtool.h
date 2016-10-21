#ifndef POINTTOOL_H
#define POINTTOOL_H

#include "tool.h"
#include "point.h"

class PointTool : public Tool
{
public:
    PointTool(Scene &scene) : Tool(scene) {}

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // POINTTOOL_H
