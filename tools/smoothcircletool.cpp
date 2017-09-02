#include "smoothcircletool.h"

void SmoothCircleTool::mousePressEvent(QMouseEvent *event)
{
    circle = new SmoothCircle(scene, event->pos(), 0, scene.foregroundColor());
    scene.addObject(circle);
}
