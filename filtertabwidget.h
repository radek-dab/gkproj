#ifndef FILTERTABWIDGET_H
#define FILTERTABWIDGET_H

#include "filter.h"
#include <QTabWidget>

namespace Ui {
class FilterTabWidget;
}

class FilterTabWidget : public QTabWidget
{
    Q_OBJECT
    Q_PROPERTY(Filter * filter READ filter NOTIFY filterChanged)

public:
    explicit FilterTabWidget(QWidget *parent = 0);
    ~FilterTabWidget();

    Filter * filter() const
        { return _filter; }

signals:
    void filterChanged(Filter *);

private slots:
    void updateFilter();

private:
    Ui::FilterTabWidget *ui;
    Filter *_filter;
};

#endif // FILTERTABWIDGET_H
