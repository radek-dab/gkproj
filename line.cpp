#include "line.h"
#include "dist.h"

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
    put(rst, x, y);

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
            put(rst, x, y);
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
            put(rst, x, y);
        }
    }
}

bool Line::hit(const QPoint &p)
{
    int len2 = dist2(_start, _end);
    int d2;

    if (len2 == 0) {
        d2 = dist2(_start, p);
    } else {
        double t = (double)QPoint::dotProduct(p-_start, _end-_start) / len2;
        t = qBound(0.0, t, 1.0);
        QPoint proj = _start + t * (_end-_start);
        d2 = dist2(proj, p);
    }

    int hitArea = qMax(int(HIT_AREA), _thickness>>1);
    return d2 < hitArea*hitArea;
}

void Line::move(const QPoint &p)
{
    _start += p;
    _end += p;
}
