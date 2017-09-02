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
    enum ShadeType { Wireframe, Flat };

    Object3D(Scene &scene, quint32 color,
             const QString &name = QString("Object 3D %1").arg(++counter))
        : Drawable(scene, name, color),
          near(0.1), far(10), fov(M_PI/3),
          origin(0, 0, -2), light(5, 5, 5),
          rotx(0), roty(0), _scale(1),
          _shadeType(Wireframe), _normalsVisible(false) {}

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

    ShadeType shadeType() const
        { return _shadeType; }
    void setShadeType(ShadeType type)
        { _shadeType = type; }

    bool isNormalsVisible() const
        { return _normalsVisible; }
    void setNormalsVisible(bool visible)
        { _normalsVisible = visible; }
    void flipNormals();

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

    // Computed variables
    QVector<QVector3D> _normals;
    QVector<QVector3D> _centers;

    float near, far;
    float fov;          // Field of view
    QVector3D origin;
    QVector3D light;
    float rotx, roty;   // Rotation
    float _scale;
    ShadeType _shadeType;
    bool _normalsVisible;

    void computeNormals();
    void computeCenters();
    QMatrix4x4 perspective(float ratio);
};

inline void Object3D::flipNormals()
{
    for (auto it = _normals.begin(); it != _normals.end(); it++)
        *it = -*it;
}

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
