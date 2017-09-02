#ifndef MATRIXFILTER_H
#define MATRIXFILTER_H

#include "filter.h"
#include "matrix.h"

class MatrixFilter : public Filter
{
public:
    MatrixFilter(const Matrix &mat)
        : _mat(mat) {}

    const Matrix & matrix() const
        { return _mat; }
    void setMatrix(const Matrix &mat)
        { _mat = mat; }

    void apply(Raster &rst, const QRect &win);

private:
    Matrix _mat;
};

#endif // MATRIXFILTER_H
