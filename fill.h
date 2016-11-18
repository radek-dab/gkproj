#ifndef FILL_H
#define FILL_H

#include "drawable.h"

class Fill : public Drawable
{
public:
    Fill(Scene &scene, const QPoint pos, quint32 color)
        : Drawable(scene, QString("Fill %1").arg(++counter), color),
          _pos(pos) {}

    QPoint pos() const
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

#endif // FILL_H
