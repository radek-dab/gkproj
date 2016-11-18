#include "clipwindow.h"

void ClipWindow::draw(Raster &rst)
{
    // Draw horizontal lines
    for (int x = _rect.left(); x <= _rect.right(); x++) {
        rst(x, _rect.top()) = _color;
        rst(x, _rect.bottom()) = _color;
    }

    // Draw vertical lines
    for (int y = _rect.top(); y <= _rect.bottom(); y++) {
        rst(_rect.left(), y) = _color;
        rst(_rect.right(), y) = _color;
    }
}
