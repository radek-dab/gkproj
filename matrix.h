#ifndef MATRIX_H
#define MATRIX_H

#include "raster.h"

class Matrix
{
public:
    Matrix(int size)
        : _size(size), r(size >> 1),
          _mat(size * size)
        { Q_ASSERT(size & 1); }

    int size() const
        { return _size; }
    int radius() const
        { return r; }

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

private:
    int _size, r;
    QVector<int> _mat;
};

#endif // MATRIX_H
