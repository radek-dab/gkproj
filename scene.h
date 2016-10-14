#ifndef SCENE_H
#define SCENE_H

#include "drawable.h"
#include <QList>

class Scene //: public Drawable
{
public:
    Scene(quint32 bg)
        : background(bg) {}

    void draw(Raster &rst);
    bool hit(const QPoint &p);

private:
    QList<Drawable*> objects;
    quint32 background;
};

#endif // SCENE_H
