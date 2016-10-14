#ifndef GRID_H
#define GRID_H

#include <QtGlobal>
#include <QSize>
#include <QPoint>
#include "raster.h"

class Grid
{
public:
    Grid(quint32 color, QSize size, QPoint offset = QPoint(0, 0)) :
        color(color),
        size(size),
        offset(offset.x() % size.width(), offset.y() % size.height())
    {}

    void draw(Raster &rst);

private:
    quint32 color;
    QSize size;
    QPoint offset;
};

#endif // GRID_H
