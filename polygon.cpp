#include "polygon.h"
#include "line.h"
#include <QDebug>

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

    updateEdges();
}

void Polygon::addEdge(const QPoint &a, const QPoint &b)
{
    float slope = float(b.x() - a.x()) / (b.y() - a.y());

    if (a.y() < b.y())
        _edges.push_back({a.y(), b.y(), float(a.x()), slope});
    else
        _edges.push_back({b.y(), a.y(), float(b.x()), slope});
}

void Polygon::updateEdges()
{
    _edges.clear();

    for (int i = 1; i < _vertices.count(); i++)
        addEdge(_vertices[i-1], _vertices[i]);
    addEdge(_vertices.first(), _vertices.last());

    std::sort(_edges.begin(), _edges.end(),
        [](const Edge &e, const Edge &f) {
            return e.ymin < f.ymin;
        });

    qDebug() << "Edge table:";
    foreach (Edge e, _edges)
        qDebug() << " " << e.ymin << e.ymax << e.x << e.slope;
}
