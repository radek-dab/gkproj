#include "scene.h"

void Scene::draw(Raster &rst)
{
    rst.clear(background);
    foreach (Drawable *obj, objects) {
        obj->draw(rst);
    }
}

bool Scene::hit(const QPoint &p)
{
    Q_UNUSED(p);
    return true;
}
