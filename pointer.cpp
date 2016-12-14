#include "pointer.h"

void Pointer::mousePressEvent(QMouseEvent *event)
{
    scene.selectObject(pointingIdx);
    lastPos = event->pos();
}

void Pointer::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        scene.selectedObject()->move(event->pos() - lastPos);
        lastPos = event->pos();
        scene.update();
    } else {
        for (int i = scene.objects().count()-1; i >= 0; i--) {
            if (scene.objects()[i]->hit(event->pos())) {
                pointingIdx = i;
                scene.setCursor(Qt::SizeAllCursor);
                return;
            }
        }
        pointingIdx = -1;
        scene.setCursor(Qt::ArrowCursor);
    }
}

void Pointer::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}
