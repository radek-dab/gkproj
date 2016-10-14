#ifndef LINE_H
#define LINE_H

#include "raster.h"
#include <QPoint>

class Line
{
public:
    Line(QPoint start, QPoint end, quint32 color)
        : start(start), end(end), color(color) {}

    void draw(Raster &rst);

private:
    QPoint start;
    QPoint end;
    quint32 color;
};

#endif // LINE_H
