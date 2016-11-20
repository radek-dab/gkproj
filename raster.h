#ifndef RASTER_H
#define RASTER_H

#include <QImage>

class Raster
{
public:
    static const quint32 BLACK = 0xFF000000;
    static const quint32 GREY  = 0xFF7F7F7F;
    static const quint32 WHITE = 0xFFFFFFFF;
    static const quint32 RED   = 0xFFFF0000;
    static const quint32 GREEN = 0xFF00FF00;
    static const quint32 BLUE  = 0xFF0000FF;

    static quint8 alpha(quint32 color)
        { return color>>24 & 255; }
    static quint8 red(quint32 color)
        { return color>>16 & 255; }
    static quint8 green(quint32 color)
        { return color>>8 & 255; }
    static quint8 blue(quint32 color)
        { return color & 255; }

    static quint32 makeColor(quint8 red, quint8 green, quint8 blue)
        { return 0xFF000000 | red<<16 | green<<8 | blue; }

    const int w;
    const int h;

    Raster(int w, int h) :
        w(w), h(h), _pixels(new quint32[w*h]()) {}

    Raster(int w, int h, quint32 color) :
        Raster(w, h) { clear(color); }

    Raster(const QImage &img) :
        w(img.width()), h(img.height()),
        _pixels(new quint32[img.width() * img.height()])
    {
        quint32 *dest = _pixels;
        for (int y = 0; y < h; y++) {
            quint32 *src = (quint32 *)img.constScanLine(y);
            for (int x = 0; x < w; x++)
                *dest++ = *src++;
        }
    }

    ~Raster()
        { delete[] _pixels; }

    const quint32 * pixels() const
        { return _pixels; }

    quint32 & operator ()(int x, int y)
    {
        Q_ASSERT(0 <= x && x < w);
        Q_ASSERT(0 <= y && y < h);

        return _pixels[w*y + x];
    }

    bool get(int x, int y, quint32 &color)
    {
        if (0 <= x && x < w && 0 <= y && y < h) {
            color = _pixels[w*y + x];
            return true;
        } else {
            return false;
        }
    }

    void put(int x, int y, quint32 color)
    {
        if (0 <= x && x < w && 0 <= y && y < h)
            _pixels[w*y + x] = color;
    }

    void mixin(int x, int y, quint32 color, double alpha)
    {
        if (x < 0 || w <= x || y < 0 || h <= y)
            return;

        quint32 backcol = _pixels[w*y + x];

        quint8 r = red(color)   * alpha + red(backcol)   * (1-alpha);
        quint8 g = green(color) * alpha + green(backcol) * (1-alpha);
        quint8 b = blue(color)  * alpha + blue(backcol)  * (1-alpha);

        _pixels[w*y + x] = makeColor(r, g, b);
    }

    void clear(quint32 color)
    {
        int n = w*h;
        for (int i = 0; i < n; i++)
            _pixels[i] = color;
    }

private:
    quint32 *_pixels;
};

#endif // RASTER_H
