#ifndef HISTOGRAMWIDGET_H
#define HISTOGRAMWIDGET_H

#include "scene.h"
#include "histogramchannelwidget.h"
#include <QWidget>
#include <QVBoxLayout>

class HistogramWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HistogramWidget(QWidget *parent = 0);

public slots:
    void analyze(Scene *scene);

private:
    QVBoxLayout *layout;
    HistogramChannelWidget *red, *green, *blue;
};

#endif // HISTOGRAMWIDGET_H
