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
    int size = ui->sizeSpinBox->value();
    QColor color = ui->colorEdit->color();

    return Grid(size, color.rgba());
}

void GridDialog::setGrid(const Grid &grid)
{
    ui->sizeSpinBox->setValue(grid.size());
    ui->colorEdit->setColor(grid.color());
}
