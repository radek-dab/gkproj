#include "filterwidget.h"
#include "ui_filterwidget.h"
#include "scalingfilter.h"
#include "histogramstretchingfilter.h"

FilterWidget::FilterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilterWidget),
    _filter(NULL)
{
    ui->setupUi(this);
    updateFilter();
}

FilterWidget::~FilterWidget()
{
    delete ui;
}

void FilterWidget::updateFilter()
{
    if (_filter)
        delete _filter;

    int type = ui->comboBox->currentIndex();
    if (type == Scaling) {
        float factor = ui->factorSpinBox->value();
        _filter = new ScalingFilter(factor);
    } else if (type == HistogramStretching) {
        float threshold = ui->thresholdSpinBox->value() / 100.0f;
        _filter = new HistogramStretchingFilter(threshold);
    } else {
        _filter = NULL;
    }

    filterChanged(_filter);
}
