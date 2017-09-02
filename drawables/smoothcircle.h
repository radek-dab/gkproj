#ifndef SMOOTHCIRCLE_H
#define SMOOTHCIRCLE_H

#include "circle.h"

class SmoothCircle : public Circle
{
public:
    SmoothCircle(Scene &scene, const QPoint &center, int radius, quint32 color,
                 const QString name
                    = QString("Smooth circle %1").arg(++counter))
        : Circle(scene, center, radius, color, name) {}

    void draw(Raster &rst);

protected:
    void put16(Raster &rst, int x, int y, double intens);

private:
    static int counter;
};

inline void SmoothCircle::put16(Raster &rst, int x, int y, double intens)
{
    rst.mixin(c.x() + x,   c.y() + y,   color(), 1-intens);
    rst.mixin(c.x() + x-1, c.y() + y,   color(), intens);
    rst.mixin(c.x() + x,   c.y() - y,   color(), 1-intens);
    rst.mixin(c.x() + x-1, c.y() - y,   color(), intens);

    rst.mixin(c.x() - x,   c.y() + y,   color(), 1-intens);
    rst.mixin(c.x() - x+1, c.y() + y,   color(), intens);
    rst.mixin(c.x() - x,   c.y() - y,   color(), 1-intens);
    rst.mixin(c.x() - x+1, c.y() - y,   color(), intens);

    rst.mixin(c.x() + y,   c.y() + x,   color(), 1-intens);
    rst.mixin(c.x() + y,   c.y() + x-1, color(), intens);
    rst.mixin(c.x() + y,   c.y() - x,   color(), 1-intens);
    rst.mixin(c.x() + y,   c.y() - x+1, color(), intens);

    rst.mixin(c.x() - y,   c.y() + x,   color(), 1-intens);
    rst.mixin(c.x() - y,   c.y() + x-1, color(), intens);
    rst.mixin(c.x() - y,   c.y() - x,   color(), 1-intens);
    rst.mixin(c.x() - y,   c.y() - x+1, color(), intens);
}

#endif // SMOOTHCIRCLE_H
