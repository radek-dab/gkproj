#include "filltool.h"

void FillTool::mousePressEvent(QMouseEvent *event)
{
    Fill *fill = new Fill(scene, event->pos(), scene.foregroundColor(),
                          _method, _boundary, _neighborhood);
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
