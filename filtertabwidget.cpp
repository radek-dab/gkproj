#include "filtertabwidget.h"
#include "ui_filtertabwidget.h"
#include "histogramstretchingfilter.h"

FilterTabWidget::FilterTabWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::FilterTabWidget),
    _filter(NULL)
{
    ui->setupUi(this);
    updateFilter();
}

FilterTabWidget::~FilterTabWidget()
{
    delete ui;
}

void FilterTabWidget::updateFilter()
{
    if (_filter)
        delete _filter;

    if (ui->histogramTab == currentWidget()) {
        float threshold = ui->thresholdSpinBox->value() / 100.0f;
        _filter = new HistogramStretchingFilter(threshold);
    } else {
        _filter = NULL;
    }

    filterChanged(_filter);
}
