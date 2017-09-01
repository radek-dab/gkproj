#include "function.h"

int Function::segment(quint8 x) const
{
    for (int i = 0; i < _points.count(); i++)
        if (x < _points[i].x())
            return i-1;

    return -1;
}

quint8 Function::operator ()(quint8 x) const
{
    const int seg = segment(x);
    if (seg == -1)
        return 0;

    const QPoint &a = _points[seg];
    const QPoint &b = _points[seg+1];
    float m = float(b.y() - a.y()) / (b.x() - a.x());
    float y = a.y() + m * (x - a.x());

    return qRound(y);
}

void Function::replace(int idx, const QPoint &p)
{
    if (idx < 0 || idx >= _points.count())
        return;

    QPoint q(0, qBound(0, p.y(), 255));
    if (idx == 0) {
        q.setX(0);
    } else if (idx < _points.count()-1) {
        int min = _points[idx-1].x() + 1;
        int max = _points[idx+1].x() - 1;
        q.setX(qBound(min, p.x(), max));
    } else {
        q.setX(255);
    }
    _points[idx] = q;
}
