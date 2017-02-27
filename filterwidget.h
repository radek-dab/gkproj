#ifndef FILTERWIDGET_H
#define FILTERWIDGET_H

#include "filter.h"
#include <QWidget>

namespace Ui {
class FilterWidget;
}

class FilterWidget : public QWidget
{
    Q_OBJECT
    Q_ENUMS(FilterType)
    Q_PROPERTY(Filter * filter READ filter NOTIFY filterChanged)

public:
    enum FilterType {
        Function,
        Matrix,
        Rotation,
        Scaling,
        HistogramStretching
    };

    explicit FilterWidget(QWidget *parent = 0);
    ~FilterWidget();

    Filter * filter() const
        { return _filter; }

signals:
    void filterChanged(Filter *);

private slots:
    void updateFilter();

private:
    Ui::FilterWidget *ui;
    Filter *_filter;
};

#endif // FILTERWIDGET_H
