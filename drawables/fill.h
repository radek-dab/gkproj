#ifndef FILL_H
#define FILL_H

#include "drawable.h"

class Fill : public Drawable
{
public:
    enum Method
    {
        FloodFill,
        BoundaryFill
    };

    enum Neighborhood
    {
        FourConnected,
        EightConnected
    };

    Fill(Scene &scene,
         const QPoint pos,
         quint32 color,
         Method method = FloodFill,
         quint32 boundary = Raster::BLACK,
         Neighborhood neighborhood = FourConnected)
        : Drawable(scene, QString("Fill %1").arg(++counter), color),
          _pos(pos),
          _method(method),
          _boundary(boundary),
          _neighborhood(neighborhood) {}

    QPoint pos() const
        { return _pos; }
    void setPos(const QPoint &pos)
        { _pos = pos; }

    Method method() const
        { return _method; }
    void setMethod(Method method)
        { _method = method; }

    quint32 boundary() const
        { return _boundary; }
    void setBoundary(quint32 color)
        { _boundary = color; }

    Neighborhood neighborhood() const
        { return _neighborhood; }
    void setNeighborhood(Neighborhood neighborhood)
        { _neighborhood = neighborhood; }

    void draw(Raster &rst);
    bool hit(const QPoint &p);
    void move(const QPoint &p);

private:
    static int counter;
    QPoint _pos;
    Method _method;
    quint32 _boundary;
    Neighborhood _neighborhood;
};

#endif // FILL_H
