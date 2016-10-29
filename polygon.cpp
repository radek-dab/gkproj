#include "polygon.h"
#include "line.h"

void Polygon::draw(Raster &rst)
{
    Q_ASSERT(!_vertices.isEmpty());

    for (int i = 1; i < _vertices.count(); i++)
        Line(_vertices[i-1], _vertices[i], color()).draw(rst);

    Line(_vertices.first(), _vertices.last(), color()).draw(rst);
}

bool Polygon::hit(const QPoint &p)
{
    Q_ASSERT(!_vertices.isEmpty());

    for (int i = 1; i < _vertices.count(); i++)
        if (Line(_vertices[i-1], _vertices[i], color()).hit(p))
            return true;

    return Line(_vertices.first(), _vertices.last(), color()).hit(p);
}

void Polygon::move(const QPoint &p)
{
    for (int i = 0; i < _vertices.count(); i++)
        _vertices[i] += p;
}
