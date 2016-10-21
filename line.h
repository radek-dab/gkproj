#ifndef LINE_H
#define LINE_H

#include "drawable.h"

class Line : public Drawable
{
public:
    Line(QPoint start, QPoint end, quint32 color)
        : Drawable(QString("Line %1").arg(++counter), color),
          _start(start),
          _end(end) {}

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
};

#endif // LINE_H
