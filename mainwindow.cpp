#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "assert.h"
#include "griddialog.h"
#include "pointer.h"
#include "pointtool.h"
#include "linetool.h"
#include "circletool.h"
#include "smoothcircletool.h"
#include "polygontool.h"
#include "filldialog.h"
#include "object3d.h"
#include "manipulatetool.h"
#include <QDebug>
#include <QRadioButton>
#include <QListWidgetItem>
#include <QColorDialog>
#include <QInputDialog>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    toolGroup(new QActionGroup(this)),
    statusLabel(new QLabel(this))
{
    ui->setupUi(this);

    ui->actionPointer->setActionGroup(toolGroup);
    ui->actionPoint->setActionGroup(toolGroup);
    ui->actionLine->setActionGroup(toolGroup);
    ui->actionCircle->setActionGroup(toolGroup);
    ui->actionSmoothCircle->setActionGroup(toolGroup);
    ui->actionPolygon->setActionGroup(toolGroup);
    ui->actionFill->setActionGroup(toolGroup);
    ui->actionManipulate->setActionGroup(toolGroup);

    ui->scene->setFilter(ui->filterWidget->filter());
    ui->scene->setTool(new Pointer(*ui->scene));
    ui->actionPointer->setChecked(true);

    ui->propertiesDockContents->setEnabled(false);
    ui->filterDock->setVisible(false);
    ui->histogramDock->setVisible(false);

    ui->statusBar->addWidget(statusLabel);
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
        ui->propertiesDockContents->setEnabled(true);
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

        if (Object3D *obj3D = dynamic_cast<Object3D *>(obj)) {
            ui->object3DGroupBox->setEnabled(true);
            ui->shadeWireframeRadioButton->setChecked(
                        obj3D->shadeType() == Object3D::Wireframe);
            ui->shadeFlatRadioButton->setChecked(
                        obj3D->shadeType() == Object3D::Flat);
            ui->normalsCheckBox->setChecked(obj3D->isNormalsVisible());
        } else {
            ui->object3DGroupBox->setEnabled(false);
        }
    } else {
        ui->propertiesDockContents->setEnabled(false);
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

void MainWindow::toggleFilterWindow()
{
    ui->scene->toggleFilterWindow(ui->filterDock->isVisible() ||
                                  ui->histogramDock->isVisible());
}

void MainWindow::updateStatus()
{
    QSize size = ui->scene->size();
    int fps = ui->scene->fps();
    QString text = QString("%1x%2").arg(size.width()).arg(size.height());
    if (fps > 0)
        text += QString(" @ %1 fps").arg(fps);
    statusLabel->setText(text);
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

void MainWindow::setTool()
{
    QAction *action = qobject_cast<QAction*>(sender());
    Q_CHECK_PTR(action);

    if (action == ui->actionPointer) {
        ui->scene->setTool(new Pointer(*ui->scene));
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
    if (action == ui->actionManipulate) {
        ui->scene->setTool(new ManipulateTool(*ui->scene));
        return;
    }

    UNREACHED();
}

void MainWindow::on_actionImage_triggered()
{
    QString dir = QStandardPaths::standardLocations(
                QStandardPaths::PicturesLocation).first();
    QString path = QFileDialog::getOpenFileName(
                this, "Choose image", dir,
                "Image files (*.png *.jpg *.gif *.bmp)");
    if (path.isNull())
        return;

    addImage(path);
}

void MainWindow::on_actionObject3D_triggered()
{
    QString dir = QStandardPaths::standardLocations(
                QStandardPaths::HomeLocation).first();
    QString path = QFileDialog::getOpenFileName(
                this, "Choose object 3D", dir,
                "3D object files (*.off)");
    if (path.isNull())
        return;

    Object3D *obj = new Object3D(*ui->scene, ui->scene->foregroundColor(),
                                 QFileInfo(path).baseName());
    ui->scene->addObject(obj);

    try {
        obj->load(path);
    } catch (QString ex) {
        QMessageBox(QMessageBox::Critical, "Error", ex,
                    QMessageBox::Ok, this).exec();
        ui->scene->deleteObject();
        return;
    }

    ui->actionManipulate->trigger();
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
                "Image files (*.png *.jpg *.gif *.bmp)");
    if (path.isNull())
        return;

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

void MainWindow::setChannel()
{
    Polygon *pol = dynamic_cast<Polygon *>(ui->scene->selectedObject());
    Q_CHECK_PTR(pol);

    if (ui->rgbRadioButton->isChecked()) {
        pol->setChannel(Polygon::RGB);
        return;
    }
    if (ui->yRadioButton->isChecked()) {
        pol->setChannel(Polygon::Y);
        return;
    }
    if (ui->uRadioButton->isChecked()) {
        pol->setChannel(Polygon::U);
        return;
    }
    if (ui->vRadioButton->isChecked()) {
        pol->setChannel(Polygon::V);
        return;
    }

    UNREACHED();
}

void MainWindow::setShade()
{
    QRadioButton *radioButton = qobject_cast<QRadioButton *>(sender());
    Q_CHECK_PTR(radioButton);
    Object3D *obj = dynamic_cast<Object3D *>(ui->scene->selectedObject());
    Q_CHECK_PTR(obj);

    if (radioButton == ui->shadeWireframeRadioButton) {
        obj->setShadeType(Object3D::Wireframe);
        ui->scene->update();
        return;
    }
    if (radioButton == ui->shadeFlatRadioButton) {
        obj->setShadeType(Object3D::Flat);
        ui->scene->update();
        return;
    }

    UNREACHED();
}

void MainWindow::on_normalsCheckBox_toggled(bool checked)
{
    Object3D *obj = dynamic_cast<Object3D *>(ui->scene->selectedObject());
    Q_CHECK_PTR(obj);

    obj->setNormalsVisible(checked);
    ui->scene->update();
}

void MainWindow::on_normalsToolButton_clicked()
{
    Object3D *obj = dynamic_cast<Object3D *>(ui->scene->selectedObject());
    Q_CHECK_PTR(obj);

    obj->flipNormals();
    ui->scene->update();
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

void MainWindow::on_actionLenna_triggered()
{
    static const QString path =
            QStandardPaths::standardLocations(
                QStandardPaths::PicturesLocation).first()
            + "/Lenna.png";

    addImage(path);
}

void MainWindow::addImage(const QString &path)
{
    static const QPoint pos(50, 50);

    QImage img(path);
    if (img.isNull()) {
        QMessageBox(QMessageBox::Critical, "Error",
                    "Error occured during loading image.",
                    QMessageBox::Ok, this).exec();
        return;
    }

    Polygon *pol = new Polygon(*ui->scene, {}, ui->scene->foregroundColor(),
                               QFileInfo(path).baseName());
    ui->scene->addObject(pol);

    pol->addVertex(pos);
    pol->addVertex(pos + QPoint(img.width()-1, 0));
    pol->addVertex(pos + QPoint(img.width()-1, img.height()-1));
    pol->addVertex(pos + QPoint(0, img.height()-1));

    pol->setFill(Polygon::FILL_PATTERN);
    pol->setPattern(new Raster(img));
}
