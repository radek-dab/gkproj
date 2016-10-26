#ifndef GRID_H
#define GRID_H

#include "raster.h"

class Grid
{
public:
    Grid(int size, quint32 color)
        : _size(size), _color(color) {}

    int size() const
        { return _size; }
    void setSize(int size)
        { _size = size; }
    quint32 color() const
        { return _color; }
    void setColor(quint32 color)
        { _color = color; }

    void draw(Raster &rst);

private:
    int _size;
    quint32 _color;
};

#endif // GRID_H
