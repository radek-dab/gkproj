#include "window.h"

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
