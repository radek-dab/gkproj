#include "clipwindow.h"

QLine ClipWindow::clip(const QLine &line)
{
    int x1 = line.x1(), dx = line.dx();
    int y1 = line.y1(), dy = line.dy();
    int xmin = rect().left(), xmax = rect().right();
    int ymin = rect().top(), ymax = rect().bottom();

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
