#ifndef SMOOTHCIRCLETOOL_H
#define SMOOTHCIRCLETOOL_H

#include "circletool.h"
#include "drawables/smoothcircle.h"

class SmoothCircleTool : public CircleTool
{
public:
    SmoothCircleTool(Scene &scene) : CircleTool(scene) {}

    void mousePressEvent(QMouseEvent *event);
};

#endif // SMOOTHCIRCLETOOL_H
