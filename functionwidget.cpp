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

    // Test existing point
    for (int i = 0; i < points.count(); i++) {
        if (dist2(viewPoint(points[i]), event->pos()) < HitDist*HitDist) {
            _curridx = i;
#if DEBUG_FILTERS
            qDebug() << "Point hit:" << i;
#endif
            return;
        }
    }

    // No point hit
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
