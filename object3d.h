#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "drawable.h"
#include <cmath>
#include <QVector>
#include <QVector3D>
#include <QMatrix4x4>

class Object3D : public Drawable
{
public:
    Object3D(Scene &scene, quint32 color,
             const QString &name = QString("Object 3D %1").arg(++counter))
        : Drawable(scene, name, color),
          near(0.1), far(10), fov(M_PI/3),
          origin(0, 0, -2), light(5, 5, 5),
          _scale(1) {}

    void load(const QString &filename);

    void draw(Raster &rst);
    bool hit(const QPoint &p);
    void move(const QPoint &p);

    void rotateX(float angle) { rotx += angle; }
    void rotateY(float angle) { roty += angle; }

    float scale() const
        { return _scale; }
    void setScale(float scale)
        { _scale = scale; }

private:
    static int counter;

    struct FacePolygon
    {
        QList<QPoint> points;
        float z;
        quint32 color;
        QLine normal;

        FacePolygon(const QList<QPoint> &points, float z,
                    quint32 color, const QLine &normal)
            : points(points), z(z),
              color(color), normal(normal) {}

        bool operator <(const FacePolygon &p) const
            { return z > p.z; }
    };

    QVector<QVector3D> _vertices;
    QVector<QVector<int>> _faces;
    int _edges;

    float near, far;
    float fov;          // Field of view
    QVector3D origin;
    QVector3D light;
    float rotx, roty;   // Rotation
    float _scale;

    QMatrix4x4 perspective(float ratio);
};

inline QMatrix4x4 Object3D::perspective(float ratio)
{
    float n = near, f = far;
    float e = 1 / tan(fov/2); // Focal length
    float a = ratio;

    float m33 = -(f+n)/(f-n);
    float m34 = -2*f*n/(f-n);

    return QMatrix4x4(e,    0,      0,      0,
                      0,    e/a,    0,      0,
                      0,    0,      m33,    m34,
                      0,    0,      -1,     0);
}

#endif // OBJECT3D_H
