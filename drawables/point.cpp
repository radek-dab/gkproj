#include "point.h"
#include "dist.h"

int Point::counter = 0;

void Point::draw(Raster &rst)
{
    rst.put(_pos.x(), _pos.y(), color());
}

bool Point::hit(const QPoint &p)
{
    int d2 = dist2(_pos, p);
    return d2 < HIT_AREA*HIT_AREA;
}

void Point::move(const QPoint &p)
{
    _pos += p;
}
