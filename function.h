#ifndef FUNCTION_H
#define FUNCTION_H

#include <QVector>
#include <QPoint>

class Function
{
public:
    Function()
        { _points << QPoint(0, 0) << QPoint(255, 255); }

    const QVector<QPoint> & points() const
        { return _points; }

    int segment(quint8 x) const;

    quint8  operator ()(quint8  x) const;
    quint32 operator ()(quint32 pix) const;

    void insert(int idx, const QPoint &p);
    void replace(int idx, const QPoint &p);

private:
    QVector<QPoint> _points;
};

inline quint32 Function::operator ()(quint32 pix) const
{
    quint8 *rgb = (quint8 *)&pix;
    rgb[2] = operator ()(rgb[2]);
    rgb[1] = operator ()(rgb[1]);
    rgb[0] = operator ()(rgb[0]);
    return pix;
}

#endif // FUNCTION_H
