#ifndef CLIPWINDOW_H
#define CLIPWINDOW_H

#include "raster.h"
#include <QRect>
#include <QLine>

class ClipWindow
{
public:
    ClipWindow(QRect rect, quint32 color)
        : _rect(rect), _color(color) {}

    QRect rect() const
        { return _rect; }
    void serRect(const QRect &rect)
        { _rect = rect; }
    quint32 color() const
        { return _color; }
    void setColor(quint32 color)
        { _color = color; }

    void draw(Raster &rst);
    QLine clip(const QLine &line);

private:
    QRect _rect;
    quint32 _color;
};

#endif // CLIPWINDOW_H
