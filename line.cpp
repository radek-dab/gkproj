#include "line.h"
#include <QDebug>

int Line::counter = 0;

void Line::draw(Raster &rst)
{
    int dx, dy;
    int xi, yi;

    if (_start.x() < _end.x()) {
        dx = _end.x() - _start.x();
        xi = 1;
    } else {
        dx = _start.x() - _end.x();
        xi = -1;
    }

    if (_start.y() < _end.y()) {
        dy = _end.y() - _start.y();
        yi = 1;
    } else {
        dy = _start.y() - _end.y();
        yi = -1;
    }

    int x = _start.x(), y = _start.y();
    rst.put(x, y, color());

    if (dx > dy) {
        int ai = (dy-dx) << 1;
        int bi = dy << 1;
        int d = bi - dx;

        while (x != _end.x()) {
            if (d >= 0) {
                x += xi;
                y += yi;
                d += ai;
            } else {
                x += xi;
                d += bi;
            }
            rst.put(x, y, color());
        }
    } else {
        int ai = (dx-dy) << 1;
        int bi = dx << 1;
        int d = bi - dy;

        while (y != _end.y()) {
            if (d >= 0) {
                x += xi;
                y += yi;
                d += ai;
            } else {
                y += yi;
                d += bi;
            }
            rst.put(x, y, color());
        }
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
