#include "functionwidget.h"
#include "dist.h"
#include <QPainter>
#include <QMouseEvent>

#if DEBUG_FILTERS
#include <QDebug>
#endif

FunctionWidget::FunctionWidget(QWidget *parent)
    : QWidget(parent),
      _backcol(Qt::black),
      _forecol(Qt::white),
      _curridx(-1)
{
    emit functionChanged(_fun);
}

void FunctionWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.fillRect(0, 0, width(), height(), _backcol);

    const QVector<QPoint> &points = _fun.points();

#if DEBUG_FILTERS
    qDebug() << "Function points:";
    foreach (const QPoint &p, points)
        qDebug() << p;
#endif

    QVector<QPoint> polyline(points.count());
    for (int i = 0; i < points.count(); i++)
        polyline[i] = viewPoint(points[i]);

    painter.setPen(_forecol);
    painter.drawPolyline(polyline.constData(), polyline.count());
}

void FunctionWidget::mousePressEvent(QMouseEvent *event)
{
    int idx;

    // Test points
    if ((idx = hitPoint(event->pos())) != -1) {
#if DEBUG_FILTERS
        qDebug() << "Hit point" << idx;
#endif
        if (event->button() == Qt::LeftButton) {
            _curridx = idx;
        } else {
            _curridx = -1;
            if (event->button() == Qt::RightButton) {
                _fun.remove(idx);
                update();
                emit functionChanged(_fun);
            }
        }
        return;
    }

    // Test segments
    if ((idx = hitSegment(event->pos())) != -1) {
#if DEBUG_FILTERS
        qDebug() << "Hit segment" << idx;
#endif
        QPoint p(modelPoint(event->pos()));
        _fun.insert(idx+1, p);
        _curridx = idx+1;
        update();
        emit functionChanged(_fun);
        return;
    }

    _curridx = -1;
}

void FunctionWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (_curridx == -1)
        return;

    _fun.replace(_curridx, modelPoint(event->pos()));
    update();

    emit functionChanged(_fun);
}

void FunctionWidget::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    _curridx = -1;
}

int FunctionWidget::hitPoint(const QPoint &p)
{
    for (int i = 0; i < _fun.points().count(); i++) {
        QPoint q(viewPoint(_fun.points()[i]));
        if (dist2(p, q) < HitDist*HitDist)
            return i;
    }

    return -1;
}

int FunctionWidget::hitSegment(const QPoint &p)
{
    for (int i = 1; i < _fun.points().count(); i++) {
        QLine line(viewPoint(_fun.points()[i-1]),
                   viewPoint(_fun.points()[i]));
        if (dist(line, p) < HitDist)
            return i-1;
    }

    return -1;
}
