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
