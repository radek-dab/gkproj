#ifndef CIRCLE_H
#define CIRCLE_H

#include "drawable.h"

class Circle : public Drawable
{
public:
    Circle(const QPoint &center, int radius, quint32 color,
           const QString name = QString("Circle %1").arg(++counter))
        : Drawable(name, color), c(center), r(radius)
        { Q_ASSERT(radius >= 0); }

    QPoint center() const
        { return c; }
    void setCenter(const QPoint &center)
        { c = center; }
    int radius() const
        { return r; }
    void setRadius(int radius)
        { Q_ASSERT(radius >= 0); r = radius; }

    void draw(Raster &rst);
    bool hit(const QPoint &p);
    void move(const QPoint &p);

protected:
    QPoint c;
    int r;

    void put8(Raster &rst, int x, int y, qint32 color);

private:
    static int counter;
};

inline void Circle::put8(Raster &rst, int x, int y, qint32 color)
{
    rst.put(c.x() + x, c.y() + y, color); // 1
    rst.put(c.x() + y, c.y() + x, color); // 2
    rst.put(c.x() + y, c.y() - x, color); // 3
    rst.put(c.x() + x, c.y() - y, color); // 4
    rst.put(c.x() - x, c.y() - y, color); // 5
    rst.put(c.x() - y, c.y() - x, color); // 6
    rst.put(c.x() - y, c.y() + x, color); // 7
    rst.put(c.x() - x, c.y() + y, color); // 8
}

#endif // CIRCLE_H
