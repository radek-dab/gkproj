#include "functionfilter.h"

void FunctionFilter::apply(Raster &rst, const QRect &win)
{
    Raster original(rst);

    for (int y = win.top(); y <= win.bottom(); y++) {
        quint32 *src = &original(0, y);
        quint32 *dst = &rst(0, y);
        for (int x = win.left(); x <= win.right(); x++)
            dst[x] = _fun(src[x]);
    }
}
