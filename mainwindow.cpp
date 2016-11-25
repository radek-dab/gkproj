#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "griddialog.h"
#include "movetool.h"
#include "pointtool.h"
#include "linetool.h"
#include "circletool.h"
#include "smoothcircletool.h"
#include "polygontool.h"
#include "filldialog.h"
#include <QDebug>
#include <QRadioButton>
#include <QListWidgetItem>
#include <QColorDialog>
#include <QInputDialog>
#include <QFileDialog>
#include <QStandardPaths>

#define UNREACHED() Q_ASSERT_X(0, __FUNCTION__, "should not be reached")

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    toolGroup(new QActionGroup(this)),
    sizeLabel(new QLabel(this))
{
    ui->setupUi(this);

    ui->actionMove->setActionGroup(toolGroup);
    ui->actionPoint->setActionGroup(toolGroup);
    ui->actionLine->setActionGroup(toolGroup);
    ui->actionCircle->setActionGroup(toolGroup);
    ui->actionSmoothCircle->setActionGroup(toolGroup);
    ui->actionPolygon->setActionGroup(toolGroup);
    ui->actionFill->setActionGroup(toolGroup);

    ui->scene->setTool(new MoveTool(*ui->scene));
    ui->actionMove->setChecked(true);

    ui->statusBar->addWidget(sizeLabel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addObject(Drawable *obj)
{
    ui->outlineList->addItem(obj->name());
}

void MainWindow::selectObject(int idx)
{
    qDebug() << "Select:" << idx;
    ui->outlineList->setCurrentRow(idx);

    if (idx != -1) {
        Drawable *obj = ui->scene->objects()[idx];
        ui->propertiesDock->setEnabled(true);
        ui->nameEdit->setText(obj->name());
        ui->colorEdit->setColor(obj->color());

        if (Polygon *pol = dynamic_cast<Polygon *>(obj)) {
            ui->polygonGroupBox->setEnabled(true);
            ui->fillNoneRadioButton->setChecked(
                        pol->fill() == Polygon::FILL_NONE);
            ui->fillSolidRadioButton->setChecked(
                        pol->fill() == Polygon::FILL_SOLID);
            ui->fillPatternRadioButton->setChecked(
                        pol->fill() == Polygon::FILL_PATTERN);
        } else {
            ui->polygonGroupBox->setEnabled(false);
        }
    } else {
        ui->propertiesDock->setEnabled(false);
    }
}

void MainWindow::reorderObject(int from, int to)
{
    qDebug() << "Reorder object:" << from << "->" << to;
    ui->outlineList->blockSignals(true); // Selection is changing.
    QListWidgetItem *item = ui->outlineList->takeItem(from);
    ui->outlineList->insertItem(to, item);
    ui->outlineList->blockSignals(false);
}

void MainWindow::deleteObject(int idx)
{
    qDebug() << "Delete object:" << idx;
    ui->outlineList->blockSignals(true); // Selection is changing.
    delete ui->outlineList->takeItem(idx);
    ui->outlineList->blockSignals(false);
}

void MainWindow::renameObject(int idx, const QString &name)
{
    ui->outlineList->item(idx)->setText(name);
}

void MainWindow::on_actionForegroundColor_triggered()
{
    QColor color = QColorDialog::getColor(ui->scene->foregroundColor(), this);
    if (!color.isValid()) return;
    ui->scene->setForegroundColor(color.rgba());
    qDebug() << "Foreground color:" << color;
}

void MainWindow::on_actionBackgroundColor_triggered()
{
    QColor color = QColorDialog::getColor(ui->scene->backgroundColor(), this);
    if (!color.isValid()) return;
    ui->scene->setBackgroundColor(color.rgba());
    qDebug() << "Background color:" << color;
}

void MainWindow::on_actionConfigureGrid_triggered()
{
    GridDialog dialog(this);
    dialog.setGrid(ui->scene->grid());
    if (dialog.exec() == QDialog::Accepted) {
        ui->scene->setGrid(dialog.grid());
    }
}

void MainWindow::on_scene_resized()
{
    QSize size = ui->scene->size();
    QString text = QString("%1x%2").arg(size.width()).arg(size.height());
    sizeLabel->setText(text);
}

void MainWindow::setTool()
{
    QAction *action = qobject_cast<QAction*>(sender());
    Q_CHECK_PTR(action);

    if (action == ui->actionMove) {
        ui->scene->setTool(new MoveTool(*ui->scene));
        return;
    }
    if (action == ui->actionPoint) {
        ui->scene->setTool(new PointTool(*ui->scene));
        return;
    }
    if (action == ui->actionLine) {
        int d = QInputDialog::getInt(this, "Line", "Line thickness",
                                     1, 0, 9999);
        ui->scene->setTool(new LineTool(*ui->scene, d));
        return;
    }
    if (action == ui->actionCircle) {
        ui->scene->setTool(new CircleTool(*ui->scene));
        return;
    }
    if (action == ui->actionSmoothCircle) {
        ui->scene->setTool(new SmoothCircleTool(*ui->scene));
        return;
    }
    if (action == ui->actionPolygon) {
        ui->scene->setTool(new PolygonTool(*ui->scene));
        return;
    }
    if (action == ui->actionFill) {
        FillDialog fillDialog(this);
        fillDialog.exec();
        ui->scene->setTool(fillDialog.getTool(*ui->scene));
        return;
    }

    UNREACHED();
}

void MainWindow::setFill()
{
    QRadioButton *radioButton = qobject_cast<QRadioButton *>(sender());
    Q_CHECK_PTR(radioButton);
    Polygon *pol = dynamic_cast<Polygon *>(ui->scene->selectedObject());
    Q_CHECK_PTR(pol);

    if (radioButton == ui->fillNoneRadioButton) {
        pol->setFill(Polygon::FILL_NONE);
        ui->scene->update();
        return;
    }
    if (radioButton == ui->fillSolidRadioButton) {
        pol->setFill(Polygon::FILL_SOLID);
        ui->scene->update();
        return;
    }
    if (radioButton == ui->fillPatternRadioButton) {
        pol->setFill(Polygon::FILL_PATTERN);
        ui->scene->update();
        return;
    }

    UNREACHED();
}

void MainWindow::on_fillPatternToolButton_clicked()
{
    QString dir = QStandardPaths::standardLocations(
                QStandardPaths::PicturesLocation).first();
    QString path = QFileDialog::getOpenFileName(
                this, "Choose pattern", dir,
                "Images files (*.png *.jpg *.gif *.bmp)");
    if (path.isNull()) return;
    qDebug() << "Chosen pattern:" << path;
    Raster *pattern = new Raster(QImage(path));
    qDebug("Pattern size: %dx%d", pattern->w, pattern->h);

    Polygon *pol = dynamic_cast<Polygon *>(ui->scene->selectedObject());
    Q_CHECK_PTR(pol);
    pol->setPattern(pattern);
}

void MainWindow::on_reduceSlider_valueChanged(int value)
{
    Polygon *pol = dynamic_cast<Polygon *>(ui->scene->selectedObject());
    Q_CHECK_PTR(pol);
    pol->setReduction(value);
}

void MainWindow::on_actionComb_triggered()
{
    Polygon *comb = new Polygon(*ui->scene, {}, ui->scene->foregroundColor());
    ui->scene->addObject(comb);

    QPoint p(50, 50);
    int width = 200, height = 80;
    int nTooth = 40, hTooth = 60;
    int d = width/nTooth;

    comb->addVertex(p);
    for (int i = 1; i <= nTooth; i++) {
        comb->addVertex(p + QPoint(i*d - d/2, hTooth));
        comb->addVertex(p + QPoint(i*d, 0));
    }
    comb->addVertex(p + QPoint(width, height));
    comb->addVertex(p + QPoint(0, height));
}
