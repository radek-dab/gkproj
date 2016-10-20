#ifndef CIRCLE_H
#define CIRCLE_H

#include "drawable.h"

class Circle : public Drawable
{
public:
    Circle(const QPoint &center, int radius, quint32 color);

    int radius();
    void setRadius(int radius);

    void inflate(const QPoint &p);
    void draw(Raster &rst);
    bool hit(const QPoint &p);
    void move(const QPoint &p);

private:
    static int counter;
    int r;
};

inline Circle::Circle(const QPoint &center, int radius, quint32 color)
    : Drawable(center, color), r(radius)
{
    Q_ASSERT(radius >= 0);
    _name = QString("Circle %1").arg(++counter);
}

inline int Circle::radius()
{
    return r;
}

inline void Circle::setRadius(int radius)
{
    Q_ASSERT(radius >= 0);
    r = radius;
}

#endif // CIRCLE_H
