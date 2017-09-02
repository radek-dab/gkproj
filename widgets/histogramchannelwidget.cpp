#include "histogramchannelwidget.h"
#include <cmath>
#include <QPainter>

void HistogramChannelWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.fillRect(0, 0, width(), height(), Qt::black);

    int x1, x2 = 0;
    double m = (double)width()/256;
    int scale = _scale > 0 ? _scale : max();
    for (int i = 1; i <= 256; i++) {
        x1 = x2;
        x2 = round(i * m);
        int w = x2 - x1;
        int h = round((double)_data[i-1]/scale * height());
        painter.fillRect(x1, height()-h, w, h, _color);
    }
}
