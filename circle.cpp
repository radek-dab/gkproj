#include "circle.h"
#include "dist.h"

int Circle::counter = 0;

static inline void put8(Raster &rst, int cx, int cy,
                        int x, int y, qint32 color)
{
    rst.put(cx + x, cy + y, color); // 1
    rst.put(cx + y, cy + x, color); // 2
    rst.put(cx + y, cy - x, color); // 3
    rst.put(cx + x, cy - y, color); // 4
    rst.put(cx - x, cy - y, color); // 5
    rst.put(cx - y, cy - x, color); // 6
    rst.put(cx - y, cy + x, color); // 7
    rst.put(cx - x, cy + y, color); // 8
}

void Circle::draw(Raster &rst)
{
    int deltaE = 3;
    int deltaSE = 5 - 2*r;
    int d = 1 - r;
    int x = 0;
    int y = r;

    put8(rst, c.x(), c.y(), x, y, color());
    while (y > x) {
        if (d < 0) {
            d += deltaE;
            deltaE += 2;
            deltaSE += 2;
        } else {
            d += deltaSE;
            deltaE += 2;
            deltaSE += 4;
            y--;
        }
        x++;
        put8(rst, c.x(), c.y(), x, y, color());
    }
}

bool Circle::hit(const QPoint &p)
{
    double d = dist(c, p);
    return r-HIT_AREA < d && d < r+HIT_AREA;
}

void Circle::move(const QPoint &p)
{
    c += p;
}
