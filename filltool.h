#ifndef FILLTOOL_H
#define FILLTOOL_H

#include "tool.h"
#include "fill.h"

class FillTool : public Tool
{
public:
    FillTool(Scene &scene) : Tool(scene) {}

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // FILLTOOL_H
