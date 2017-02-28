#ifndef ROTATIONFILTER_H
#define ROTATIONFILTER_H

#include "filter.h"

class RotationFilter : public Filter
{
public:
    RotationFilter(float angle = 0)
        : _angle(angle) {}

    float angle() const
        { return _angle; }
    void setAngle(float angle)
        { _angle = angle; }

    void apply(Raster &rst, const QRect &win);

private:
    float _angle;
};

#endif // ROTATIONFILTER_H
