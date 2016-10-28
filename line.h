#ifndef LINE_H
#define LINE_H

#include "drawable.h"

class Line : public Drawable
{
public:
    Line(QPoint start, QPoint end, quint32 color)
        : Drawable(QString("Line %1").arg(++counter), color),
          _start(start),
          _end(end),
          _thickness(1) {}
    Line(QPoint start, QPoint end, int thickness, quint32 color)
        : Line(start, end, color) { _thickness = thickness; }

    QPoint start()
        { return _start; }
    void setStart(const QPoint &start)
        { _start = start; }

    QPoint end()
        { return _end; }
    void setEnd(const QPoint &end)
        { _end = end; }

    void draw(Raster &rst);
    bool hit(const QPoint &p);
    void move(const QPoint &p);

private:
    static int counter;
    QPoint _start;
    QPoint _end;
    int _thickness;

    void put(Raster &rst, int x, int y);
};

inline void Line::put(Raster &rst, int x, int y)
{
    if (_thickness == 1) {
        rst.put(x, y, color());
        return;
    }

    int a = -(_thickness>>1);
    int b = _thickness + a;

    for (int j = a; j < b; j++)
        for (int i = a+abs(j); i < b-abs(j); i++)
            rst.put(x+i, y+j, color());
}

#endif // LINE_H
