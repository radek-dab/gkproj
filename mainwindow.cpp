#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "griddialog.h"
#include "movetool.h"
#include "pointtool.h"
#include "linetool.h"
#include "circletool.h"
#include "smoothcircletool.h"
#include "polygontool.h"
#include "filltool.h"
#include <QDebug>
#include <QColorDialog>
#include <QListWidgetItem>
#include <QInputDialog>

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
        ui->nameEdit->setText(obj->name());
        ui->colorEdit->setColor(obj->color());
    } else {
        ui->nameEdit->setText("");
        ui->colorEdit->setColor(Qt::white);
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
        ui->scene->setTool(new FillTool(*ui->scene));
        return;
    }
}
