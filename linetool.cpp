#include "linetool.h"

void LineTool::mousePressEvent(QMouseEvent *event)
{
    line = new Line(event->pos(), event->pos(),
                    thickness, scene.foregroundColor());
    scene.addObject(line);
}

void LineTool::mouseMoveEvent(QMouseEvent *event)
{
    line->setEnd(event->pos());
    scene.update();
}

void LineTool::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}
