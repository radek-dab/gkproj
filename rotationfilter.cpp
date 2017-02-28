#include "rotationfilter.h"
#include <QMatrix4x4>

void RotationFilter::apply(Raster &rst, const QRect &win)
{
    Raster original(rst);
    QMatrix4x4 mat;
    mat.rotate(-_angle, 0, 0, 1);

    for (int y = win.top(); y <= win.bottom(); y++) {
        quint32 *scanline = &rst(0, y);
        for (int x = win.left(); x <= win.right(); x++) {
            QPointF r = QPoint(x, y) - win.center();
            r = mat.map(r);
            QPoint p = r.toPoint() + win.center();

            if (win.contains(p))
                scanline[x] = original(p.x(), p.y());
            else
                scanline[x] = Raster::BLACK;
        }
    }
}
