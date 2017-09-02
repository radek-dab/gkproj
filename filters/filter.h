#ifndef FILTER_H
#define FILTER_H

#include "models/raster.h"

class Filter
{
public:
    virtual ~Filter() {}
    virtual void apply(Raster &rst, const QRect &win) = 0;
};

#endif // FILTER_H
