#include "circletool.h"
#include "dist.h"

void CircleTool::mousePressEvent(QMouseEvent *event)
{
    circle = new Circle(event->pos(), 0, scene.foregroundColor());
    scene.addObject(circle);
}

void CircleTool::mouseMoveEvent(QMouseEvent *event)
{
    int radius = dist(circle->center(), event->pos());
    circle->setRadius(radius);
    scene.update();
}

void CircleTool::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}
