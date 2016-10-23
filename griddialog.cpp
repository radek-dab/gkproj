#include "griddialog.h"
#include "ui_griddialog.h"

GridDialog::GridDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GridDialog)
{
    ui->setupUi(this);
}

GridDialog::~GridDialog()
{
    delete ui;
}

Grid GridDialog::grid() const
{
    int w = ui->widthSpinBox->value();
    int h = ui->heightSpinBox->value();
    int x = ui->xSpinBox->value();
    int y = ui->ySpinBox->value();

    return Grid(QSize(w, h), QPoint(x, y));
}

void GridDialog::setGrid(const Grid &grid)
{
    ui->widthSpinBox->setValue(grid.size().width());
    ui->heightSpinBox->setValue(grid.size().height());
    ui->xSpinBox->setValue(grid.offset().x());
    ui->ySpinBox->setValue(grid.offset().y());
}
