#ifndef DIST_H
#define DIST_H

#include <QPoint>
#include <cmath>

inline int dist2(const QPoint &p1, const QPoint &p2)
{
    int dx = p1.x() - p2.x();
    int dy = p1.y() - p2.y();
    return dx*dx + dy*dy;
}

inline double dist(const QPoint &p1, const QPoint &p2)
{
    return sqrt(dist2(p1, p2));
}

#endif // DIST_H
