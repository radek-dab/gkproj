#ifndef GAMMAFILTER_H
#define GAMMAFILTER_H

#include "filter.h"

class GammaFilter : public Filter
{
public:
    GammaFilter(float gamma = 1)
        : _gamma(gamma) {}

    float gamma() const
        { return _gamma; }
    void setGamma(float gamma)
        { _gamma = gamma; }

    void apply(Raster &rst, const QRect &win);

private:
    float _gamma;
};

#endif // GAMMAFILTER_H
