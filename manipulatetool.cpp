#include "manipulatetool.h"

const float ManipulateTool::DEGREES_PER_PIX = 1.0;

void ManipulateTool::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void ManipulateTool::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton))
        return;

    Object3D *obj = dynamic_cast<Object3D *>(scene.selectedObject());
    if (!obj)
        return;

    QPoint d = event->pos() - lastPos;
    obj->rotateY(d.x() * DEGREES_PER_PIX);
    obj->rotateX(d.y() * DEGREES_PER_PIX);

    lastPos = event->pos();
    scene.update();
}

void ManipulateTool::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}
