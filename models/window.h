#ifndef WINDOW_H
#define WINDOW_H

#include "raster.h"
#include "common/assert.h"

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

    enum Action
    {
        NoAction,
        Move,
        ResizeNW,
        ResizeSE,
        ResizeNE,
        ResizeSW
    };

    static Qt::CursorShape cursor(Action action);
    static const int HitArea = 10;

    Action hit(const QPoint &p) const;
    void act(Action action, const QPoint &p);

private:
    QRect _rect;
    quint32 _color;
};

inline Qt::CursorShape Window::cursor(Action action)
{
    switch (action) {
    case Move:
        return Qt::SizeAllCursor;
    case ResizeNW:
    case ResizeSE:
        return Qt::SizeFDiagCursor;
    case ResizeNE:
    case ResizeSW:
        return Qt::SizeBDiagCursor;
    default:
        return Qt::ArrowCursor;
    }

    UNREACHED();
}

#endif // WINDOW_H
