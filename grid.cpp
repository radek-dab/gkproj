#include "grid.h"

void Grid::draw(Raster &rst, QRect clipping)
{
    if (clipping.isNull())
        clipping = QRect(0, 0, rst.w, rst.h);

    // Draw vertical lines
    for (int x = clipping.left(); x < clipping.right(); x += _size)
        for (int y = clipping.top(); y < clipping.bottom(); y++)
            rst(x, y) = _color;

    // Draw horizontal lines
    for (int y = clipping.top(); y < clipping.bottom(); y += _size)
        for (int x = clipping.left(); x < clipping.right(); x++)
            rst(x, y) = _color;
}
