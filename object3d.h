#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "drawable.h"
#include <QVector>
#include <QVector3D>
#include <QMatrix4x4>

class Object3D : public Drawable
{
public:
    Object3D(Scene &scene, quint32 color)
        : Drawable(scene, QString("Object 3D %1").arg(++counter), color) {}

    void load(const QString &filename);

    void draw(Raster &rst);
    bool hit(const QPoint &p);
    void move(const QPoint &p);

private:
    static int counter;

    QVector<QVector3D> _vertices;
    QVector<QVector<int>> _faces;
    int _edges;
};

#endif // OBJECT3D_H
