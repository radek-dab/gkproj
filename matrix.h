#ifndef MATRIX_H
#define MATRIX_H

#include "raster.h"

class Matrix
{
public:
    Matrix(int size)
        : _size(size), r(size >> 1),
          _mat(size * size),
          _divisor(1)
        { Q_ASSERT(size & 1); }

    int size() const
        { return _size; }
    int radius() const
        { return r; }

    int divisor() const
        { return _divisor; }
    void setDivisor(int divisor)
        { _divisor = divisor; }

    int & operator [](int i)
    {
        Q_ASSERT(0 <= i && i < _mat.size());
        return _mat[i];
    }

    int & operator ()(int i, int j)
    {
        Q_ASSERT(-r <= i && i <= r);
        Q_ASSERT(-r <= j && j <= r);
        return _mat[_size * (j+1) + (i+1)];
    }

    quint32 map(const Raster &rst, int x, int y);
    void setToGaussianBlur();

private:
    int _size, r;
    QVector<int> _mat;
    int _divisor;
};

#endif // MATRIX_H
