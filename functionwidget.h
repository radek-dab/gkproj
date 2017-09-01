#ifndef FUNCTIONWIDGET_H
#define FUNCTIONWIDGET_H

#include <QWidget>
#include "function.h"

class FunctionWidget : public QWidget
{
    Q_OBJECT

public:
    static const int HitDist = 10;

    explicit FunctionWidget(QWidget *parent = 0);

    const Function & function() const
        { return _fun; }

signals:
    void functionChanged(const Function &fun);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Function _fun;
    QColor _backcol;
    QColor _forecol;
    int _curridx;

    QPoint viewPoint(const QPoint &p);
    QPoint modelPoint(const QPoint &p);

    void insert(int idx, const QPoint &p);
    void replace(int idx, const QPoint &p);
    void remove(int idx);

    int hitPoint(const QPoint &p);
    int hitSegment(const QPoint &p);
};

inline QPoint FunctionWidget::viewPoint(const QPoint &p)
{
    int w = width();
    int x = float(p.x()) / 255 * (w-1);

    int h = height();
    int y = float(255 - p.y()) / 255 * (h-1);

    return QPoint(x, y);
}

inline QPoint FunctionWidget::modelPoint(const QPoint &p)
{
    int w = width();
    int x = float(p.x()) / (w-1) * 255;

    int h = height();
    int y = float(h-1 - p.y()) / (h-1) * 255;

    return QPoint(x, y);
}

inline void FunctionWidget::insert(int idx, const QPoint &p)
{
    _fun.insert(idx, modelPoint(p));
    update();
    emit functionChanged(_fun);
}

inline void FunctionWidget::replace(int idx, const QPoint &p)
{
    _fun.replace(idx, modelPoint(p));
    update();
    emit functionChanged(_fun);
}

inline void FunctionWidget::remove(int idx)
{
    _fun.remove(idx);
    update();
    emit functionChanged(_fun);
}

#endif // FUNCTIONWIDGET_H
