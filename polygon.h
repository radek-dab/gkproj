#ifndef POLYGON_H
#define POLYGON_H

#include "drawable.h"
#include <QList>

class Polygon : public Drawable
{
public:
    enum FillType
    {
        FILL_NONE,
        FILL_SOLID,
        FILL_PATTERN
    };

    Polygon(Scene &scene, const QList<QPoint> &vertices, quint32 color,
            const QString &name = QString("Polygon %1").arg(++counter))
        : Drawable(scene, name, color),
          _vertices(vertices),
          _fill(FILL_NONE),
          _pattern(NULL)
        { updateEdges(); }

    ~Polygon()
        { if (_pattern) delete _pattern; }

    void addVertex(const QPoint &p)
        { _vertices.push_back(p);  updateEdges(); }
    void setVertex(const QPoint &p)
        { _vertices.last() = p; updateEdges(); }
    void deleteVertex()
        { _vertices.pop_back(); updateEdges(); }

    FillType fill() const
        { return _fill; }
    void setFill(FillType fill)
        { _fill = fill; }
    const Raster * pattern() const
        { return _pattern; }
    void setPattern(Raster *pattern)
        { if (_pattern) delete _pattern; _pattern = pattern; }

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
    FillType _fill;
    Raster *_pattern;

    void addEdge(const QPoint &a, const QPoint &b);
    void updateEdges();
    void put(Raster &rst, int x, int y);
};

inline void Polygon::put(Raster &rst, int x, int y)
{
    if (_fill == FILL_SOLID)
        rst.put(x, y, color());
    if (_fill == FILL_PATTERN && _pattern != NULL)
        rst.put(x, y, _pattern->getm(x - _vertices.first().x(),
                                     y - _vertices.first().y()));
}

#endif // POLYGON_H
