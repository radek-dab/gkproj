#include "window.h"
#include <QDebug>

void Window::draw(Raster &rst)
{
    // Draw horizontal lines
    for (int x = _rect.left(); x <= _rect.right(); x++) {
        rst.put(x, _rect.top(), _color);
        rst.put(x, _rect.bottom(), _color);
    }

    // Draw vertical lines
    for (int y = _rect.top(); y <= _rect.bottom(); y++) {
        rst.put(_rect.left(), y, _color);
        rst.put(_rect.right(), y, _color);
    }
}

Window::Action Window::hit(const QPoint &p) const
{
    // Test bounding box
    if (p.x() < rect().left()-HitArea || rect().right()+HitArea < p.x() ||
        p.y() < rect().top()-HitArea || rect().bottom()+HitArea < p.y())
        return NoAction;

    // Match area
    if (p.y() < rect().top()+HitArea) {
        // Near top edge
        if (p.x() < rect().left()+HitArea)
            return ResizeNW;
        if (p.x() < rect().right()-HitArea)
            return Move;
        return ResizeNE;
    } else if (p.y() < rect().bottom()-HitArea) {
        // Between top and bottom edge
        if (p.x() < rect().left()+HitArea)
            return Move;
        if (p.x() < rect().right()-HitArea)
            return NoAction;
        return Move;
    } else {
        // Near bottom edge
        if (p.x() < rect().left()+HitArea)
            return ResizeSW;
        if (p.x() < rect().right()-HitArea)
            return Move;
        return ResizeSE;
    }

    UNREACHED();
}

void Window::act(Action action, const QPoint &p)
{
    switch (action) {
    case Move:
        _rect.translate(p);
        break;
    case ResizeNW:
        _rect.setTopLeft(_rect.topLeft() + p);
        break;
    case ResizeSE:
        _rect.setBottomRight(_rect.bottomRight() + p);
        break;
    case ResizeNE:
        _rect.setTopRight(_rect.topRight() + p);
        break;
    case ResizeSW:
        _rect.setBottomLeft(_rect.bottomLeft() + p);
        break;
    default:
        break;
    }

    qDebug() << "Window:" << _rect;
}
