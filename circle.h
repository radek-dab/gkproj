#ifndef CIRCLE_H
#define CIRCLE_H

#include "drawable.h"

class Circle : public Drawable
{
public:
    Circle(const QPoint &center, int radius, quint32 color);

    QPoint center();
    void setCenter(const QPoint &center);
    int radius();
    void setRadius(int radius);

    void inflate(const QPoint &p);
    void draw(Raster &rst);
    bool hit(const QPoint &p);
    void move(const QPoint &p);

private:
    static int counter;
    QPoint c;
    int r;
};

inline Circle::Circle(const QPoint &center, int radius, quint32 color)
    : Drawable(QString("Circle %1").arg(++counter), color),
      c(center),
      r(radius)
{
    Q_ASSERT(radius >= 0);
}

inline QPoint Circle::center()
{
    return c;
}

inline void Circle::setCenter(const QPoint &center)
{
    c = center;
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
