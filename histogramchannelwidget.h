#ifndef HISTOGRAMCHANNELWIDGET_H
#define HISTOGRAMCHANNELWIDGET_H

#include <algorithm>
#include <QWidget>
#include <QVector>

class HistogramChannelWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HistogramChannelWidget(QWidget *parent = 0)
        : QWidget(parent), _color(Qt::white), _data(256), _scale(-1) {}

    QColor color() const
        { return _color; }
    void setColor(const QColor &color)
        { _color = color; }

    void increase(int idx)
        { Q_ASSERT(0 <= idx && idx < 256); _data[idx]++; }
    int max() const
        { return *std::max_element(_data.begin(), _data.end()); }
    void clear()
        { _data.fill(0); }

    int scale() const
        { return _scale; }
    void setScale(int scale)
        { _scale = scale; }

protected:
    void paintEvent(QPaintEvent *event);

private:
    QColor _color;
    QVector<int> _data;
    int _scale;
};

#endif // HISTOGRAMCHANNELWIDGET_H
