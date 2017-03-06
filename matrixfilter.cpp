#include "matrixfilter.h"

void MatrixFilter::apply(Raster &rst, const QRect &win)
{
    Raster original(rst);

    for (int y = win.top(); y <= win.bottom(); y++) {
        quint32 *scanline = &rst(0, y);
        for (int x = win.left(); x <= win.right(); x++)
            scanline[x] = _mat.get(original, x, y);
    }
}
