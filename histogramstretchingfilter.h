#ifndef HISTOGRAMSTRETCHINGFILTER_H
#define HISTOGRAMSTRETCHINGFILTER_H

#include "filter.h"

class HistogramStretchingFilter : public Filter
{
public:
    HistogramStretchingFilter(float threshold = 0.05)
        : _threshold(threshold) {}

    float threshold() const
        { return _threshold; }
    void setThreshold(float threshold)
        { _threshold = threshold; }

    void apply(Raster &rst, const QRect &win);

private:
    float _threshold;
};

#endif // HISTOGRAMSTRETCHINGFILTER_H
