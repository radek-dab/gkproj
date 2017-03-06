#include "matrix.h"

quint32 Matrix::get(const Raster &rst, int x, int y)
{
    int red = 0, green = 0, blue = 0, scale = 0;
    auto it = _mat.begin();
    for (int my = -r; my <= r; my++)
        for (int mx = -r; mx <= r; mx++) {
            Q_ASSERT(it != _mat.end());
            quint32 col;
            if (rst.get(x + mx, y + my, col)) {
                red += (float) Raster::red(col) * (*it);
                green += (float) Raster::green(col) * (*it);
                blue += (float) Raster::blue(col) * (*it);
                scale += *it;
            }
            it++;
        }

    quint32 result = Raster::makeColor(qRound((float) red / scale),
                                       qRound((float) green / scale),
                                       qRound((float) blue / scale));
    return result;
}
