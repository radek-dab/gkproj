#ifndef POLYGON_H
#define POLYGON_H

#include "drawable.h"
#include <QList>

class Polygon : public Drawable
{
public:
    Polygon(const QList<QPoint> &vertices, quint32 color,
            const QString name = QString("Polygon %1").arg(++counter))
        : Drawable(name, color), _vertices(vertices) { updateEdges(); }

    void addVertex(const QPoint &p)
        { _vertices.push_back(p);  updateEdges(); }
    void setVertex(const QPoint &p)
        { _vertices.last() = p; updateEdges(); }
    void deleteVertex()
        { _vertices.pop_back(); updateEdges(); }

    void draw(Raster &rst);
    bool hit(const QPoint &p);
    void move(const QPoint &p);

private:
    struct Edge
    {
        int ymin;
        int ymax;
        float x;
        float slope;
    };

    static int counter;
    QList<QPoint> _vertices;
    QList<Edge> _edges;

    void addEdge(const QPoint &a, const QPoint &b);
    void updateEdges();
};

#endif // POLYGON_H
