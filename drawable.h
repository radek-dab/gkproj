#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "raster.h"
#include <QPoint>

class Drawable
{
public:
    static const int HIT_AREA = 10;

    Drawable(const QPoint &pos, quint32 color)
        : pos(pos), color(color) {}
    virtual ~Drawable() {}

    virtual void inflate(const QPoint &p) = 0;
    virtual void draw(Raster &rst) = 0;
    virtual bool hit(const QPoint &p) = 0;
    virtual void move(const QPoint &p) = 0;

protected:
    QPoint pos;
    quint32 color;
};

#endif // DRAWABLE_H
