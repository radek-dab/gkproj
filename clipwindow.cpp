#include "clipwindow.h"

void ClipWindow::draw(Raster &rst)
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

QLine ClipWindow::clip(const QLine &line)
{
    int x1 = line.x1(), dx = line.dx();
    int y1 = line.y1(), dy = line.dy();
    int xmin = _rect.left(), xmax = _rect.right();
    int ymin = _rect.top(), ymax = _rect.bottom();

    int p[4] = {-dx, dx, -dy, dy};
    int q[4] = {x1-xmin, xmax-x1, y1-ymin, ymax-y1};
    float t1 = 0;
    float t2 = 1;

    for (int i = 0; i < 4; i++) {
        if (p[i] == 0 && q[i] < 0)
            return QLine();

        float t = (float)q[i]/p[i];
        if (p[i] < 0) {
            if (t > t1)
                t1 = t;
        } else {
            if (t < t2)
                t2 = t;
        }
    }

    if (t1 > t2)
        return QLine();

    return QLine(x1 + t1*dx,
                 y1 + t1*dy,
                 x1 + t2*dx,
                 y1 + t2*dy);
}
