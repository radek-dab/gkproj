#ifndef POINTER_H
#define POINTER_H

#include "tool.h"

class Pointer : public Tool
{
public:
    Pointer(Scene &scene)
        : Tool(scene), pointingIdx(-1) {}

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    int pointingIdx;
    QPoint lastPos;
};

#endif // POINTER_H
