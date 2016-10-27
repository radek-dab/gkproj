#include "smoothcircletool.h"

void SmoothCircleTool::mousePressEvent(QMouseEvent *event)
{
    circle = new SmoothCircle(event->pos(), 0, scene.foregroundColor());
    scene.addObject(circle);
}
