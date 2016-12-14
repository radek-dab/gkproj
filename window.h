#ifndef WINDOW_H
#define WINDOW_H

#include "raster.h"

class Window
{
public:
    Window(QRect rect, quint32 color)
        : _rect(rect), _color(color) {}

    QRect rect() const
        { return _rect; }
    void setRect(const QRect &rect)
        { _rect = rect; }

    quint32 color() const
        { return _color; }
    void setColor(quint32 color)
        { _color = color; }

    void draw(Raster &rst);

private:
    QRect _rect;
    quint32 _color;
};

#endif // WINDOW_H
