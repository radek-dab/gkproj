#ifndef CIRCLE_H
#define CIRCLE_H

#include "drawable.h"

class Circle : public Drawable
{
public:
    Circle(QPoint pos, int r, quint32 color)
        : Drawable(pos, color), r(r)
    {
        Q_ASSERT(r >= 0);
    }

    void inflate(const QPoint &p);
    void draw(Raster &rst);
    bool hit(const QPoint &p);
    void move(const QPoint &p);

private:
    int r;
};

#endif // CIRCLE_H
