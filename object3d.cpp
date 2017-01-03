#include "object3d.h"
#include "line.h"
#include <QFileInfo>
#include <QFile>
#include <QTextStream>

int Object3D::counter = 0;

void Object3D::load(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw QString("Cannot open file %1").arg(filename);
    QTextStream in(&file);

    QString off;
    in >> off;
    if (off != "OFF")
        throw QString("Not found OFF header");

    int v, f, e;
    in >> v >> f >> e;
    // Is at least triagle?
    if (v < 3)
        throw QString("Too few vertices");
    if (f < 1)
        throw QString("Too few faces");

    _vertices.resize(v);
    for (int i = 0; i < v; i++) {
        float x, y, z;
        in >> x >> y >> z;
        _vertices[i] = QVector3D(x, y, z);
    }

    _faces.resize(f);
    for (int i = 0; i < f; i++) {
        int num; // Number of vertices
        in >> num;
        // Face must be at least triangle
        if (num < 3)
            throw QString("Invalid face");

        _faces[i].resize(num);
        for (int j = 0; j < num; j++) {
            int idx; // Index of vertex
            in >> idx;
            // Test if vertex exists
            if (idx < 0 || idx >= v)
                throw QString("Index out of range");

            _faces[i][j] = idx;
        }
    }

    _edges = e;
}

void Object3D::draw(Raster &rst)
{
    const QVector3D pos(300, 300, 0);
    const int scale = 200;

    foreach (const QVector<int> &face, _faces) {
        for (int i = 1; i < face.count(); i++) {
            QPoint a = (_vertices[face[i-1]] * scale + pos).toPoint(),
                   b = (_vertices[face[i]] * scale + pos).toPoint();
            Line(scene, a, b, color()).draw(rst);
        }
        QPoint a = (_vertices[face.first()] * scale + pos).toPoint(),
               b = (_vertices[face.last()] * scale + pos).toPoint();
        Line(scene, a, b, color()).draw(rst);
    }
}

bool Object3D::hit(const QPoint &p)
{
    Q_UNUSED(p);
    return false;
}

void Object3D::move(const QPoint &p)
{
    Q_UNUSED(p);
}
