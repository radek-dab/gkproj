#include "pointer.h"

void Pointer::mousePressEvent(QMouseEvent *event)
{
    for (int i = scene.objects().count()-1; i >= 0; i--) {
        Drawable *obj = scene.objects()[i];
        if (obj->hit(event->pos())) {
            scene.selectObject(i);
            movingObj = obj;
            lastPos = event->pos();
            return;
        }
    }
}

void Pointer::mouseMoveEvent(QMouseEvent *event)
{
    if (movingObj) {
        movingObj->move(event->pos() - lastPos);
        lastPos = event->pos();
        scene.update();
    }
}

void Pointer::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    movingObj = NULL;
}
