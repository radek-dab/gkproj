#ifndef POINTER_H
#define POINTER_H

#include "tool.h"

class Pointer : public Tool
{
public:
    Pointer(Scene &scene)
        : Tool(scene), action(Window::NoAction), object(-1) {}

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Window::Action action;
    int object;
    QPoint lastPos;
};

#endif // POINTER_H
