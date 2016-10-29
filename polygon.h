#ifndef POLYGON_H
#define POLYGON_H

#include "drawable.h"
#include <QList>

class Polygon : public Drawable
{
public:
    Polygon(const QList<QPoint> &vertices, quint32 color,
            const QString name = QString("Polygon %1").arg(++counter))
        : Drawable(name, color), _vertices(vertices) {}

    void addVertex(const QPoint &p)
        { _vertices.push_back(p); }
    void setVertex(const QPoint &p)
        { _vertices.last() = p; }
    void deleteVertex()
        { _vertices.pop_back(); }

    void draw(Raster &rst);
    bool hit(const QPoint &p);
    void move(const QPoint &p);

private:
    static int counter;
    QList<QPoint> _vertices;
};

#endif // POLYGON_H
