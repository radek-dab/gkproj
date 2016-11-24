#ifndef FILLTOOL_H
#define FILLTOOL_H

#include "tool.h"
#include "fill.h"

class FillTool : public Tool
{
public:
    FillTool(Scene &scene,
             Fill::Method method = Fill::FloodFill,
             quint32 boundary = Raster::BLACK,
             Fill::Neighborhood neighborhood = Fill::FourConnected)
        : Tool(scene),
          _method(method),
          _boundary(boundary),
          _neighborhood(neighborhood) {}

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Fill::Method _method;
    quint32 _boundary;
    Fill::Neighborhood _neighborhood;
};

#endif // FILLTOOL_H
