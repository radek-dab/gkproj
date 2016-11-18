#include "polygon.h"
#include "line.h"
#include <QDebug>

void Polygon::draw(Raster &rst)
{
    Q_ASSERT(!_vertices.isEmpty());

//    for (int i = 1; i < _vertices.count(); i++)
//        Line(_vertices[i-1], _vertices[i], color()).draw(rst);
//    Line(_vertices.first(), _vertices.last(), color()).draw(rst);

    auto et = _edges.begin();
    int scanline = et->ymin;
    QList<Edge> activeEdges;

    do {
        while (et != _edges.end() && et->ymin == scanline) {
            // Add active edge
            activeEdges.push_back(*et++);
            // Sort by x
            int i = activeEdges.count()-1, j = i-1;
            while (j >= 0 && activeEdges[j].x > activeEdges[i].x) j--;
            activeEdges.move(i, j+1);
        }

        // Draw lines
        for (int i = 1; i < activeEdges.count(); i += 2)
            for (int x = activeEdges[i-1].x; x <= activeEdges[i].x; x++)
                rst.put(x, scanline, color()); // TODO: Direct assignment

        // Go to next scanline
        scanline++;
        for (int i = 0; i < activeEdges.count(); i++) {
            if (activeEdges[i].ymax <= scanline) {
                // Remove inactive edge
                activeEdges.removeAt(i--);
            } else {
                // Update x
                activeEdges[i].x += activeEdges[i].slope;
                // Sort by x
                int j = i-1;
                while (j >= 0 && activeEdges[j].x > activeEdges[i].x) j--;
                activeEdges.move(i, j+1);
            }
        }
    } while (et != _edges.end() || !activeEdges.empty());
}

bool Polygon::hit(const QPoint &p)
{
    Q_ASSERT(!_vertices.isEmpty());

    for (int i = 1; i < _vertices.count(); i++)
        if (Line(scene, _vertices[i-1], _vertices[i], color()).hit(p))
            return true;

    return Line(scene, _vertices.first(), _vertices.last(), color()).hit(p);
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
