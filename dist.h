#ifndef DIST_H
#define DIST_H

#include <QPoint>
#include <cmath>

inline double dist(const QPoint &p1, const QPoint &p2)
{
    int dx = p1.x() - p2.x();
    int dy = p1.y() - p2.y();
    return sqrt(dx*dx + dy*dy);
}

#endif // DIST_H
