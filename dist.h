#ifndef DIST_H
#define DIST_H

#include <QtMath>
#include <QPoint>
#include <QLine>

inline int dist2(const QPoint &p1, const QPoint &p2)
{
    int dx = p1.x() - p2.x();
    int dy = p1.y() - p2.y();
    return dx*dx + dy*dy;
}

inline qreal dist(const QPoint &p1, const QPoint &p2)
{
    return qSqrt(dist2(p1, p2));
}

inline qreal dist(const QLine &line, const QPoint &p)
{
    int a = line.dy() * p.x()
          - line.dx() * p.y()
          + line.x2() * line.y1()
          - line.y2() * line.x1();

    int b = line.dy() * line.dy()
          + line.dx() * line.dx();

    return qAbs(a) / qSqrt(b);
}

#endif // DIST_H
