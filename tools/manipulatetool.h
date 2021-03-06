#ifndef MANIPULATETOOL_H
#define MANIPULATETOOL_H

#include "tool.h"
#include "drawables/object3d.h"

class ManipulateTool : public Tool
{
public:
    static const float DEGREES_PER_PIX;
    static const float SCALE_FACTOR;

    ManipulateTool(Scene &scene) : Tool(scene) {}

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void wheelEvent(QWheelEvent *event);

private:
    QPoint lastPos;
};

#endif // MANIPULATETOOL_H
