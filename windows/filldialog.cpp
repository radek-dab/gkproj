#include "filldialog.h"
#include "ui_filldialog.h"

FillDialog::FillDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FillDialog)
{
    ui->setupUi(this);
    ui->boundaryColorEdit->setColor(Qt::black);
}

FillDialog::~FillDialog()
{
    delete ui;
}

FillTool * FillDialog::getTool(Scene &scene)
{
    Fill::Method method =
            ui->floodRadioButton->isChecked() ? Fill::FloodFill
                                              : Fill::BoundaryFill;

    quint32 boundary = ui->boundaryColorEdit->color().rgba();

    Fill::Neighborhood neighborhood =
            ui->fourConnectedRadioButton->isChecked() ? Fill::FourConnected
                                                      : Fill::EightConnected;

    return new FillTool(scene, method, boundary, neighborhood);
}
