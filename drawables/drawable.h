#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "widgets/scene.h"
#include <QPoint>
#include <QString>

class Scene;

class Drawable
{
public:
    static const int HIT_AREA = 10;

    Drawable(Scene &scene, const QString &name, quint32 color)
        : scene(scene), _name(name), _color(color) {}
    virtual ~Drawable() {}

    QString name()
        { return _name; }
    void setName(const QString &name)
        { _name = name; }

    quint32 color()
        { return _color; }
    void setColor(quint32 color)
        { _color = color; }

    virtual void draw(Raster &rst) = 0;
    virtual bool hit(const QPoint &p) = 0;
    virtual void move(const QPoint &p) = 0;

protected:
    Scene &scene;

private:
    QString _name;
    quint32 _color;
};

#endif // DRAWABLE_H
