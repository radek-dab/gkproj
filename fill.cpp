#include "fill.h"
#include <QQueue>
#include <QDebug>
#include <QElapsedTimer>

int Fill::counter = 0;

void Fill::draw(Raster &rst)
{
    quint32 oldcol = rst(_pos.x(), _pos.y());
    quint32 newcol = color();
    quint32 col;

    QQueue<QPoint> queue;
    queue.enqueue(_pos);

    QElapsedTimer timer;
    timer.start();

    while (!queue.empty()) {
        QPoint p = queue.dequeue();

        if (!rst.get(p.x(), p.y(), col) || col != oldcol)
            continue;

        rst(p.x(), p.y()) = newcol;
        queue.enqueue(p + QPoint( 1,  0));
        queue.enqueue(p + QPoint( 0, -1));
        queue.enqueue(p + QPoint(-1,  0));
        queue.enqueue(p + QPoint( 0,  1));
    }

    qDebug() << "Filling" << timer.nsecsElapsed()/1e6 << "ms";
}

bool Fill::hit(const QPoint &p)
{
    Q_UNUSED(p);
    return false;
}

void Fill::move(const QPoint &p)
{
    Q_UNUSED(p);
}
