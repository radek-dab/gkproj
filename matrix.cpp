#include "matrix.h"

#if DEBUG_MATRIX
#include <QDebug>
#endif

quint32 Matrix::map(const Raster &rst, int x, int y)
{
    int red = 0, green = 0, blue = 0;
    auto it = _mat.begin();
    for (int my = -r; my <= r; my++)
        for (int mx = -r; mx <= r; mx++) {
            Q_ASSERT(it != _mat.end());
            quint32 col;
            if (rst.get(x + mx, y + my, col)) {
                red += (float) Raster::red(col) * (*it);
                green += (float) Raster::green(col) * (*it);
                blue += (float) Raster::blue(col) * (*it);
            }
            it++;
        }

    red = qBound(0, red, 255);
    green = qBound(0, green, 255);
    blue = qBound(0, blue, 255);
    return Raster::makeColor(red, green, blue);
}

void Matrix::setToGaussianBlur()
{
    // Compute coefficients from Pascal's triangle
    QVector<int> pascal(_size);
    for (int i = 0; i < _size; i++) {
        pascal[i] = 1;
        for (int j = i-1; j > 0; j--)
            pascal[j] += pascal[j-1];
    }

#if DEBUG_MATRIX
    qDebug() << "Pascal's triangle row" << _size << "=" << pascal;
#endif

    // Compute matrix product
    auto *it = _mat.begin();
    for (int i = 0; i < _size; i++)
        for (int j = 0; j < _size; j++)
            *it++ = pascal[i] * pascal[j];

#if DEBUG_MATRIX
    qDebug() << "Gaussian blur matrix size" << _size;
    it = _mat.begin();
    for (int i = 0; i < _size; i++) {
        QDebug d = qDebug();
        for (int j = 0; j < _size; j++)
            d << *it++ << '\t';
    }
#endif
}
