#include "circle.h"
#include "common/dist.h"

int Circle::counter = 0;

void Circle::draw(Raster &rst)
{
    int deltaE = 3;
    int deltaSE = 5 - 2*r;
    int d = 1 - r;
    int x = 0;
    int y = r;

    put8(rst, x, y, color());
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
        put8(rst, x, y, color());
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
