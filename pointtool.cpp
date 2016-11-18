#include "pointtool.h"

void PointTool::mousePressEvent(QMouseEvent *event)
{
    Point *p = new Point(scene, event->pos(), scene.foregroundColor());
    scene.addObject(p);
}

void PointTool::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}

void PointTool::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}
