#include "circletool.h"
#include "dist.h"

void CircleTool::mousePressEvent(QMouseEvent *event)
{
    circle = new Circle(scene, event->pos(), 0, scene.foregroundColor());
    scene.addObject(circle);
}

void CircleTool::mouseMoveEvent(QMouseEvent *event)
{
    if (!event->buttons()) return;
    int radius = dist(circle->center(), event->pos());
    circle->setRadius(radius);
    scene.update();
}

void CircleTool::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}
