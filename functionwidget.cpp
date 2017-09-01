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
    const QVector<QPoint> &points = _fun.points();

    // Test points
    for (int i = 0; i < points.count(); i++) {
        QPoint p(viewPoint(points[i]));
        if (dist2(p, event->pos()) < HitDist*HitDist) {
#if DEBUG_FILTERS
            qDebug() << "Hit point" << i;
#endif
            _curridx = i;
            return;
        }
    }

    // Test segments
    for (int i = 1; i < points.count(); i++) {
        QLine line(viewPoint(points[i-1]), viewPoint(points[i]));
        if (dist(line, event->pos()) < HitDist) {
#if DEBUG_FILTERS
            qDebug() << "Hit segment" << i;
#endif
            QPoint p(modelPoint(event->pos()));
            _fun.insert(i, p);
            _curridx = i;
            return;
        }
    }

    // No hit
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
