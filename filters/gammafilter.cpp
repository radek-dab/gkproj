#include "gammafilter.h"
#include <cmath>

void GammaFilter::apply(Raster &rst, const QRect &win)
{
    for (int y = win.top(); y <= win.bottom(); y++) {
        quint32 *scanline = &rst(0, y);
        for (int x = win.left(); x <= win.right(); x++) {
            quint8 r = Raster::red(scanline[x]);
            r = static_cast<quint8>(pow(r / 255.0f, _gamma) * 255);

            quint8 g = Raster::green(scanline[x]);
            g = static_cast<quint8>(pow(g / 255.0f, _gamma) * 255);

            quint8 b = Raster::blue(scanline[x]);
            b = static_cast<quint8>(pow(b / 255.0f, _gamma) * 255);

            scanline[x] = Raster::makeColor(r, g, b);
        }
    }
}
