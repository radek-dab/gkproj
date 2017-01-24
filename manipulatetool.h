#ifndef MANIPULATETOOL_H
#define MANIPULATETOOL_H

#include "tool.h"
#include "object3d.h"

class ManipulateTool : public Tool
{
public:
    static const float DEGREES_PER_PIX;

    ManipulateTool(Scene &scene) : Tool(scene) {}

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    QPoint lastPos;
};

#endif // MANIPULATETOOL_H
