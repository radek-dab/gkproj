#ifndef LINETOOL_H
#define LINETOOL_H

#include "tool.h"
#include "line.h"

class LineTool : public Tool
{
public:
    LineTool(Scene &scene) : Tool(scene) {}

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Line *line;
};

#endif // LINETOOL_H
