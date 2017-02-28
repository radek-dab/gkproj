#include "scalingfilter.h"

void ScalingFilter::apply(Raster &rst, const QRect &win)
{
    Raster original(rst);

    for (int y = win.top(); y <= win.bottom(); y++) {
        quint32 *scanline = &rst(0, y);
        for (int x = win.left(); x <= win.right(); x++) {
            QPointF r = QPoint(x, y) - win.center();
            r /= _factor;
            QPoint p = r.toPoint() + win.center();

            if (win.contains(p))
                scanline[x] = original(p.x(), p.y());
            else
                scanline[x] = Raster::BLACK;
        }
    }
}
