#ifndef CIRCLE_H
#define CIRCLE_H

#include "drawable.h"

class Circle : public Drawable
{
public:
    Circle(const QPoint &pos, int r, quint32 color)
        : Drawable(pos, color), r(r)
    {
        Q_ASSERT(r >= 0);
        _name = QString("Circle %1").arg(++counter);
    }

    void inflate(const QPoint &p);
    void draw(Raster &rst);
    bool hit(const QPoint &p);
    void move(const QPoint &p);

private:
    static int counter;
    int r;
};

#endif // CIRCLE_H
