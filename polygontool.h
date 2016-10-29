#ifndef POLYGONTOOL_H
#define POLYGONTOOL_H

#include "tool.h"
#include "polygon.h"

class PolygonTool : public Tool
{
public:
    PolygonTool(Scene &scene) : Tool(scene), polygon(NULL) {}

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Polygon *polygon;
};

#endif // POLYGONTOOL_H
