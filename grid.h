#ifndef GRID_H
#define GRID_H

#include "raster.h"
#include <QSize>
#include <QPoint>

class Grid
{
public:
    Grid(QSize size,
         QPoint offset = QPoint(0, 0),
         quint32 color = Raster::GREY)
        : _size(size),
          _offset(offset.x() % size.width(), offset.y() % size.height()),
          _color(color) {}

    QSize size() const
        { return _size; }
    void setSize(const QSize &size)
        { _size = size; }
    QPoint offset() const
        { return _offset; }
    void setOffset(const QPoint &offset)
        { _offset = offset; }
    quint32 color() const
        { return _color; }
    void setColor(quint32 color)
        { _color = color; }

    void draw(Raster &rst);

private:
    QSize _size;
    QPoint _offset;
    quint32 _color;
};

#endif // GRID_H
