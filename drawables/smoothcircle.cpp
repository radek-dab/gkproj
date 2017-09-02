#include "smoothcircle.h"
#include <cmath>

int SmoothCircle::counter = 0;

void SmoothCircle::draw(Raster &rst)
{
    int x = r;
    int y = 0;
    double T = 0;

    put8(rst, x, y, color());
    while (x > y+1) {
        y++;

        double idealx = sqrt(r*r - y*y);
        double intens = ceil(idealx) - idealx;

        if (intens < T)
            x--;

        put16(rst, x, y, intens);

        T = intens;
    }
}
