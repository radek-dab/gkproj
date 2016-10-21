#include "point.h"
#include "dist.h"

int Point::counter = 0;

void Point::draw(Raster &rst)
{
    rst.put(_pos.x(), _pos.y(), color());
}

bool Point::hit(const QPoint &p)
{
    double d = dist(_pos, p);
    return d < HIT_AREA;
}

void Point::move(const QPoint &p)
{
    _pos += p;
}
