#include "line.h"
#include <QDebug>

int Line::counter = 0;

void Line::draw(Raster &rst)
{
    int dx = _end.x() - _start.x();
    int dy = _end.y() - _start.y();

    int d = 2*dy - dx;
    int incrE = 2*dy;
    int incrNE = 2*(dy-dx);
    int x = _start.x();
    int y = _start.y();

    rst.put(x, y, color());
    while (x < _end.x()) {
        if (d < 0) {
            d += incrE;
            x++;
        } else {
            d += incrNE;
            x++;
            y++;
        }
        rst.put(x, y, color());
    }
}

bool Line::hit(const QPoint &p)
{
    return false; // TODO
}

void Line::move(const QPoint &p)
{
    _start += p;
    _end += p;
}
