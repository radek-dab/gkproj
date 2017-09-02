#include "line.h"
#include "dist.h"

int Line::counter = 0;

void Line::draw(Raster &rst)
{
    QLine line(_start, _end);
    if (scene.isClipWindowVisible()) {
        line = scene.clipWindow().clip(QLine(_start, _end));
        if (line.isNull())
            return;
    }

    int x1 = line.x1(), y1 = line.y1();
    int x2 = line.x2(), y2 = line.y2();
    int dx, dy;
    int xi, yi;

    if (x1 < x2) {
        dx = x2 - x1;
        xi = 1;
    } else {
        dx = x1 - x2;
        xi = -1;
    }

    if (y1 < y2) {
        dy = y2 - y1;
        yi = 1;
    } else {
        dy = y1 - y2;
        yi = -1;
    }

    int x = x1, y = y1;
    put(rst, x, y);

    if (dx > dy) {
        int ai = (dy-dx) << 1;
        int bi = dy << 1;
        int d = bi - dx;

        while (x != x2) {
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

        while (y != y2) {
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
