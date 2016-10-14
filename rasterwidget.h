#ifndef RASTERWIDGET_H
#define RASTERWIDGET_H

#include "raster.h"
#include "drawable.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMouseEvent>
#include <QList>

class RasterWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    RasterWidget(QWidget *parent);
    ~RasterWidget();
    Raster& raster()
        { return *rst; }
    void setForegroundColor(quint32 color);
    void setForegroundColor(const QColor &color);
    void setBackgroundColor(quint32 color);
    void setBackgroundColor(const QColor &color);
protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    Raster *rst;
    quint32 foregroundColor;
    quint32 backgroundColor;
    QList<Drawable*> objects;
    Drawable *inflatingObj;
    Drawable *draggingObj;
    QPoint draggingPos;
    quint32 convertColor(const QColor &color);
};

inline void RasterWidget::setForegroundColor(quint32 color)
{
    foregroundColor = color;
    update();
}

inline void RasterWidget::setForegroundColor(const QColor &color)
{
    foregroundColor = convertColor(color);
    update();
}

inline void RasterWidget::setBackgroundColor(quint32 color)
{
    backgroundColor = color;
    update();
}

inline void RasterWidget::setBackgroundColor(const QColor &color)
{
    backgroundColor = convertColor(color);
    update();
}

inline quint32 RasterWidget::convertColor(const QColor &color)
{
    return color.red()<<16 | color.green()<<8 | color.blue();
}

#endif // RASTERWIDGET_H
