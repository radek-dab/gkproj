#include "filltool.h"

void FillTool::mousePressEvent(QMouseEvent *event)
{
    Fill *fill = new Fill(event->pos(), scene.foregroundColor());
    scene.addObject(fill);
}

void FillTool::mouseMoveEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}

void FillTool::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}
