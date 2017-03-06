#include "filterwidget.h"
#include "ui_filterwidget.h"
#include "matrixfilter.h"
#include "rotationfilter.h"
#include "scalingfilter.h"
#include "histogramstretchingfilter.h"
#include <QLineEdit>
#include <QIntValidator>

FilterWidget::FilterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilterWidget),
    _filter(NULL)
{
    ui->setupUi(this);
    changeMatrixSize();
}

FilterWidget::~FilterWidget()
{
    delete ui;
}

void FilterWidget::changeMatrixSize()
{
    QLayoutItem *item;
    while ((item = ui->matrixGridLayout->takeAt(0)) != NULL) {
        delete item->widget();
        delete item;
    }

    int size = getMatrixSize();
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
            QLineEdit *field = new QLineEdit(this);
            field->setValidator(new QIntValidator(-99, 99, this));
            if (i == j && j == size >> 1)
                field->setText("1");
            connect(field, SIGNAL(textChanged(QString)),
                    this, SLOT(updateFilter()));
            ui->matrixGridLayout->addWidget(field, i, j);
        }

    updateFilter();
}

void FilterWidget::updateFilter()
{
    if (_filter)
        delete _filter;

    int type = ui->comboBox->currentIndex();
    if (type == MatrixType) {
        int size = getMatrixSize();
        Matrix mat(size);
        for (int i = 0; i < ui->matrixGridLayout->count(); i++) {
            QWidget *widget = ui->matrixGridLayout->itemAt(i)->widget();
            Q_CHECK_PTR(widget);
            QLineEdit *field = qobject_cast<QLineEdit *>(widget);
            Q_CHECK_PTR(field);
            bool ok;
            int val = field->text().toInt(&ok);
            mat[i] = ok ? val : 0;
        }
        _filter = new MatrixFilter(mat);
    } else if (type == Rotation) {
        float angle = ui->angleSpinBox->value();
        _filter = new RotationFilter(angle);
    } else if (type == Scaling) {
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

int FilterWidget::getMatrixSize()
{
    bool ok;
    int size = ui->sizeComboBox->currentText().toInt(&ok);
    Q_ASSERT(ok);
    return size;
}
