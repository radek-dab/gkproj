#include "object3d.h"
#include "line.h"
#include "polygon.h"
#include <QDebug>
#include <QElapsedTimer>
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

    computeNormals();
    computeCenters();
}

void Object3D::draw(Raster &rst)
{
    QElapsedTimer timer;
    timer.start();

    QMatrix4x4 viewport;
    viewport.scale(rst.w/2, -rst.h/2, 1);
    viewport.translate(1, -1, 0);

    viewport *= perspective((float)rst.h/rst.w);
    viewport.translate(origin);
    viewport.rotate(rotx, 1, 0);
    viewport.rotate(roty, 0, 1);
    viewport.scale(_scale);

    quint64 preparing = timer.nsecsElapsed();
    timer.start();

    QVector<QVector3D> mapped(_vertices.size());
    for (int i = 0; i < _vertices.size(); i++)
        mapped[i] = viewport.map(_vertices[i]);

    quint64 mapping = timer.nsecsElapsed();
    timer.start();

//    foreach (const QVector<int> &face, _faces) {
//        for (int i = 1; i < face.count(); i++) {
//            QPoint a = mapped[face[i-1]].toPoint(),
//                   b = mapped[face[i]].toPoint();
//            Line(scene, a, b, color()).draw(rst);
//        }
//        QPoint a = mapped[face.first()].toPoint(),
//               b = mapped[face.last()].toPoint();
//        Line(scene, a, b, color()).draw(rst);
//    }

    QList<FacePolygon> polygons;

    for (int f = 0; f < _faces.size(); f++) {
        const QVector<int> &face = _faces[f];

        QList<QPoint> points;
        points.reserve(face.size());
        for (int i = 0; i < face.size(); i++)
            points.append(mapped[face[i]].toPoint());

        float z = std::numeric_limits<float>::min();
        for (int i = 0; i < face.size(); i++)
            if (z < mapped[face[i]].z())
                z = mapped[face[i]].z();

        QVector3D normal = _normals[f];
        QVector3D center = _centers[f];

        QVector3D dir = (light-center).normalized();
        float intensity = qMax(0.1f, QVector3D::dotProduct(normal, dir));
        quint32 col = Raster::intensity(color(), intensity);

        QLine norm;
        if (_normalsVisible)
            norm = QLine(viewport.map(center).toPoint(),
                         viewport.map(center + 0.1*normal).toPoint());

        polygons.append(FacePolygon(points, z, col, norm));
    }

    qSort(polygons);

    foreach (const FacePolygon &fp, polygons) {
        Polygon pol(scene, fp.points, fp.color);
        pol.setFill(Polygon::FILL_SOLID);
        pol.draw(rst);

        if (_normalsVisible)
            Line(scene, fp.normal.p1(), fp.normal.p2(), Raster::BLUE).draw(rst);
    }

    quint64 drawing = timer.nsecsElapsed();
    qDebug() << "Object3D:" << fixed << qSetRealNumberPrecision(3)
             << "preparing" << preparing/1e6 << "ms +"
             << "mapping" << mapping/1e6 << "ms +"
             << "drawing" << drawing/1e6 << "ms ="
             << (preparing+mapping+drawing)/1e6 << "ms";
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

void Object3D::computeNormals()
{
    _normals.resize(_faces.size());
    for (int i = 0; i < _faces.size(); i++) {
        const QVector<int> &face = _faces[i];
        QVector3D a = _vertices[face[2]] - _vertices[face[1]];
        QVector3D b = _vertices[face[0]] - _vertices[face[1]];
        _normals[i] = QVector3D::normal(a, b);
    }
}

void Object3D::computeCenters()
{
    _centers.resize(_faces.size());
    for (int i = 0; i < _faces.size(); i++) {
        const QVector<int> &face = _faces[i];
        _centers[i] = QVector3D();
        for (int j = 0; j < face.size(); j++)
            _centers[i] += _vertices[face[j]];
        _centers[i] /= face.size();
    }
}
