#include "histogramwidget.h"
#include <QDebug>
#include <QElapsedTimer>

HistogramWidget::HistogramWidget(QWidget *parent)
    : QWidget(parent),
      layout(new QVBoxLayout(this)),
      red(new HistogramChannelWidget(this)),
      green(new HistogramChannelWidget(this)),
      blue(new HistogramChannelWidget(this))
{
    red->setColor(Qt::red);
    green->setColor(Qt::green);
    blue->setColor(Qt::blue);

    layout->addWidget(red);
    layout->addWidget(green);
    layout->addWidget(blue);
}

void HistogramWidget::analyze(Scene *scene)
{
    if (!scene->isFilterWindowVisible())
        return;

    QRect win = scene->filterWindow().rect();

    QElapsedTimer timer;
    timer.start();

    red->clear();
    green->clear();
    blue->clear();

    // For each pixel in filter window
    // NOTE: First y loop for better performance
    for (int y = win.top(); y <= win.bottom(); y++)
        for (int x = win.left(); x <= win.right(); x++) {
            quint32 pix = scene->raster()(x, y);
            quint8 *rgb = (quint8 *)&pix;

            red->increase(rgb[2]);
            green->increase(rgb[1]);
            blue->increase(rgb[0]);
        }

    int scale = qMax(qMax(red->max(), green->max()), blue->max());
    red->setScale(scale);
    green->setScale(scale);
    blue->setScale(scale);

    qDebug() << "Created histogram in" << timer.nsecsElapsed()/1e6 << "ms";

    red->update();
    green->update();
    blue->update();
}
