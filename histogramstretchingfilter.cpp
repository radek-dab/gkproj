#include "histogramstretchingfilter.h"

#if DEBUG_FILTERS
#include <QDebug>
#include <QElapsedTimer>
#endif

void HistogramStretchingFilter::apply(Raster &rst, const QRect &win)
{
#if DEBUG_FILTERS
    QElapsedTimer timer;
    timer.start();
#endif

    QVector<float> red(256), green(256), blue(256);
    for (int y = win.top(); y <= win.bottom(); y++) {
        quint32 *scanline = &rst(0, y);
        for (int x = win.left(); x <= win.right(); x++) {
            quint32 pix = scanline[x];
            quint8 *rgb = (quint8 *)&pix;

            red[rgb[2]]++;
            green[rgb[1]]++;
            blue[rgb[0]]++;
        }
    }

    float scale = 0;
    scale = qMax(scale, *std::min_element(red.constBegin(),
                                          red.constEnd()));
    scale = qMax(scale, *std::min_element(green.constBegin(),
                                          green.constEnd()));
    scale = qMax(scale, *std::min_element(blue.constBegin(),
                                          blue.constEnd()));

    int threshold = _threshold * scale, min, max;
    for (min = 0; min <= 255; min++)
        if (red[min] > threshold ||
            green[min] > threshold ||
            blue[min] > threshold)
            break;
    for (max = 255; max >= 0; max--)
        if (red[max] > threshold ||
            green[max] > threshold ||
            blue[max] > threshold)
            break;

    QVector<quint8> map(256);
    for (int i = 0; i < 255; i++)
        map[i] = qRound(double(i-min) / (max-min) * 255);

#if DEBUG_FILTERS
    quint64 analyzing = timer.nsecsElapsed();
    timer.start();
#endif

    for (int y = win.top(); y <= win.bottom(); y++) {
        quint32 *scanline = &rst(0, y);
        for (int x = win.left(); x <= win.right(); x++) {
            quint32 *pix = &scanline[x];
            quint8 *rgb = (quint8 *)pix;

            rgb[2] = map[rgb[2]];
            rgb[1] = map[rgb[1]];
            rgb[0] = map[rgb[0]];
        }
    }

#if DEBUG_FILTERS
    quint64 applying = timer.nsecsElapsed();
    qDebug() << "HistogramStretchingFilter:"
             << fixed << qSetRealNumberPrecision(3)
             << "analyzing" << analyzing/1e6 << "ms +"
             << "applying" << applying/1e6 << "ms ="
             << (analyzing+applying)/1e6 << "ms";
#endif
}
