#include "circletool.h"
#include "dist.h"

void CircleTool::mousePressEvent(QMouseEvent *event)
{
    center = event->pos();
    circle = new Circle(center, 0, scene.foregroundColor());
    scene.addObject(circle);
}

void CircleTool::mouseMoveEvent(QMouseEvent *event)
{
    int radius = dist(center, event->pos());
    circle->setRadius(radius);
}

void CircleTool::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}
