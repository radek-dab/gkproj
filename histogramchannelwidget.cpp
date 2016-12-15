#include "histogramchannelwidget.h"
#include <algorithm>
#include <QPainter>

void HistogramChannelWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.fillRect(0, 0, width(), height(), Qt::black);

    double w = (double)width()/256;
    int scale = _scale > 0 ? _scale : max();
    for (int i = 0; i < 256; i++) {
        double h = (double)_data[i]/scale * height();
        painter.fillRect(i*w, height()-(int)h, w, h, _color);
    }
}
