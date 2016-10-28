#ifndef LINETOOL_H
#define LINETOOL_H

#include "tool.h"
#include "line.h"

class LineTool : public Tool
{
public:
    LineTool(Scene &scene, int thickness = 1)
        : Tool(scene), thickness(thickness) {}

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Line *line;
    int thickness;
};

#endif // LINETOOL_H
