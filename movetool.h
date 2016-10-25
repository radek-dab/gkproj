#ifndef MOVETOOL_H
#define MOVETOOL_H

#include "tool.h"

class MoveTool : public Tool
{
public:
    MoveTool(Scene &scene) : Tool(scene), movingObj(NULL) {}

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Drawable *movingObj;
    QPoint lastPos;
};

#endif // MOVETOOL_H
