#include "polygontool.h"

int Polygon::counter = 0;

void PolygonTool::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (!polygon) {
            polygon = new Polygon(scene, {event->pos(), event->pos()},
                                  scene.foregroundColor());
            scene.addObject(polygon);
            scene.setMouseTracking(true);
        } else {
            polygon->addVertex(event->pos());
            scene.update();
        }
    }
    else if (event->button() == Qt::RightButton) {
        polygon->deleteVertex();
        polygon = NULL;
        scene.setMouseTracking(false);
        scene.update();
    }
}

void PolygonTool::mouseMoveEvent(QMouseEvent *event)
{
    polygon->setVertex(event->pos());
    scene.update();
}

void PolygonTool::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
}
