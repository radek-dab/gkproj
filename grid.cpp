#include "grid.h"

void Grid::draw(Raster &rst)
{
    // Draw vertical lines
    for (int x = _offset.x(); x < rst.w; x += _size.width())
        for (int y = 0; y < rst.h; y++)
            rst(x, y) = _color;

    // Draw horizontal lines
    for (int y = _offset.y(); y < rst.h; y += _size.height())
        for (int x = 0; x < rst.w; x++)
            rst(x, y) = _color;
}
