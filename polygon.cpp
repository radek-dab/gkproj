#include "polygon.h"
#include "line.h"
#include "octree.h"
#include <QDebug>

void Polygon::draw(Raster &rst)
{
    Q_ASSERT(!_vertices.isEmpty());

    if (_fill != FILL_PATTERN || !_pattern) {
        for (int i = 1; i < _vertices.count(); i++)
            Line(scene, _vertices[i-1], _vertices[i], color()).draw(rst);
        Line(scene, _vertices.first(), _vertices.last(), color()).draw(rst);
    }

    if (_fill == FILL_NONE)
        return;

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
//            for (int x = activeEdges[i-1].x; x <= activeEdges[i].x; x++)
//                put(rst, x, scanline);
            fillScanline(rst, scanline, activeEdges[i-1].x, activeEdges[i].x);

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

void Polygon::fillScanline(Raster &rst, int y, int x1, int x2)
{
    if (y < 0 || y >= rst.h)
        return;
    Q_ASSERT(x1 <= x2);
    x1 = qMax(x1, 0);
    x2 = qMin(x2, rst.w-1);

    if (_fill == FILL_SOLID) {
        for (int x = x1; x <= x2; x++)
            rst(x, y) = color();
        return;
    }
    if (_fill == FILL_PATTERN && _pattern != NULL) {
        int xsrc = (x1 - _vertices.first().x()) % _pattern->w;
        if (xsrc < 0)
            xsrc += _pattern->w;
        int ysrc = (y - _vertices.last().y()) % _pattern->h;
        if (ysrc < 0)
            ysrc += _pattern->h;

        for (int x = x1; x <= x2; x++) {
            rst(x, y) = (*_reducedPattern)(xsrc, ysrc);
            if (++xsrc == _pattern->w)
                xsrc = 0;
        }
        return;
    }
}

void Polygon::reduce()
{
    if (!_pattern)
        return;

    if (_reducedPattern)
        delete _reducedPattern;
    _reducedPattern = new Raster(*_pattern);

    if (_reduction > 0) {
        Octree octree(*_pattern, _reduction);
        octree.map(*_reducedPattern);
    }

    if (_channel != RGB) {
        Raster &rst = *_reducedPattern;
        quint32 *end = rst.pixels() + rst.w*rst.h;
        for (quint32 *pix = rst.pixels(); pix != end; pix++) {
            int r = Raster::red(*pix);
            int g = Raster::green(*pix);
            int b = Raster::blue(*pix);

            int y = 0.299 * r + 0.587 * g  + 0.114 * b;
            int u = 0.492 * (b - y);
            int v = 0.877 * (r - y);

            y = qBound(0, y, 255);
            u = qBound(0, u, 255);
            v = qBound(0, v, 255);

            switch (_channel) {
            case Y:
                *pix = Raster::makeColor(y, y, y);
                break;
            case U:
                *pix = Raster::makeColor(u, u, u);
                break;
            case V:
                *pix = Raster::makeColor(v, v, v);
                break;
            default:
                UNREACHED();
            }
        }
    }

    scene.update();
}
