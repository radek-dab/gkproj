#ifndef POINT_H
#define POINT_H

#include "drawable.h"

class Point : public Drawable
{
public:
    Point(const QPoint &pos, quint32 color)
        : Drawable(QString("Point %1").arg(++counter), color),
          _pos(pos) {}

    QPoint pos()
        { return _pos; }
    void setPos(const QPoint &pos)
        { _pos = pos; }

    void draw(Raster &rst);
    bool hit(const QPoint &p);
    void move(const QPoint &p);

private:
    static int counter;
    QPoint _pos;
};

#endif // POINT_H
