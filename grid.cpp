#include "grid.h"

void Grid::draw(Raster &rst)
{
    // Draw vertical lines
    for (int x = offset.x(); x < rst.w; x += size.width())
        for (int y = 0; y < rst.h; y++)
            rst(x, y) = color;

    // Draw horizontal lines
    for (int y = offset.y(); y < rst.h; y += size.height())
        for (int x = 0; x < rst.w; x++)
            rst(x, y) = color;
}