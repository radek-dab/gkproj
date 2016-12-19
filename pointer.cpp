#include "pointer.h"

void Pointer::mousePressEvent(QMouseEvent *event)
{
    scene.selectObject(object);
    lastPos = event->pos();
}

void Pointer::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        if (action != Window::NoAction)
            window->act(action, event->pos() - lastPos);
        if (object != -1)
            scene.selectedObject()->move(event->pos() - lastPos);
        lastPos = event->pos();
        scene.update();
    } else {
        object = -1;
        if (scene.isFilterWindowVisible()) {
            window = &scene.filterWindow();
            action = window->hit(event->pos());
            if (action != Window::NoAction) {
                scene.setCursor(Window::cursor(action));
                return;
            }
        }
        if (scene.isClipWindowVisible()) {
            window = &scene.clipWindow();
            action = window->hit(event->pos());
            if (action != Window::NoAction) {
                scene.setCursor(Window::cursor(action));
                return;
            }
        }
        for (object = scene.objects().count()-1; object >= 0; object--) {
            if (scene.objects()[object]->hit(event->pos())) {
                scene.setCursor(Qt::SizeAllCursor);
                return;
            }
        }
        scene.setCursor(Qt::ArrowCursor);
    }
}

void Pointer::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}
