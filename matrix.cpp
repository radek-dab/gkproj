#include "matrix.h"

quint32 Matrix::map(const Raster &rst, int x, int y)
{
    int red = 0, green = 0, blue = 0;
    auto it = _mat.begin();
    for (int my = -r; my <= r; my++)
        for (int mx = -r; mx <= r; mx++) {
            Q_ASSERT(it != _mat.end());
            quint32 col;
            if (rst.get(x + mx, y + my, col)) {
                red += (float) Raster::red(col) * (*it);
                green += (float) Raster::green(col) * (*it);
                blue += (float) Raster::blue(col) * (*it);
            }
            it++;
        }

    red = qBound(0, red, 255);
    green = qBound(0, green, 255);
    blue = qBound(0, blue, 255);
    return Raster::makeColor(red, green, blue);
}
