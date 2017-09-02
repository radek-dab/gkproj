#include "grid.h"

void Grid::draw(Raster &rst, QRect clipping)
{
    if (clipping.isNull())
        clipping = QRect(0, 0, rst.w, rst.h);

    int x0 = clipping.left() + _size - clipping.left() % _size;
    int y0 = clipping.top() + _size - clipping.top() % _size;

    // Draw vertical lines
    for (int x = x0; x < clipping.right(); x += _size)
        for (int y = clipping.top(); y < clipping.bottom(); y++)
            rst.put(x, y, _color);

    // Draw horizontal lines
    for (int y = y0; y < clipping.bottom(); y += _size)
        for (int x = clipping.left(); x < clipping.right(); x++)
            rst.put(x, y, _color);
}
