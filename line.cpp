#include "line.h"
#include <QDebug>
#include <QElapsedTimer>

void Line::draw(Raster &rst)
{
    int dx = end.x() - start.x();
    int dy = end.y() - start.y();

    int d = 2*dy - dx;
    int incrE = 2*dy;
    int incrNE = 2*(dy-dx);
    int x = start.x();
    int y = start.y();

    rst(x, y) = color;
    while (x < end.x()) {
        if (d < 0) {
            d += incrE;
            x++;
        } else {
            d += incrNE;
            x++;
            y++;
        }
        rst(x, y) = color;
    }
}
