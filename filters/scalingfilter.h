#ifndef SCALINGFILTER_H
#define SCALINGFILTER_H

#include "filter.h"

class ScalingFilter : public Filter
{
public:
    ScalingFilter(float factor = 1)
        : _factor(factor) {}

    float factor() const
        { return _factor; }
    void setFactor(float factor)
        { _factor = factor; }

    void apply(Raster &rst, const QRect &win);

private:
    float _factor;
};

#endif // SCALINGFILTER_H
