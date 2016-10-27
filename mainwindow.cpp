#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "griddialog.h"
#include "movetool.h"
#include "pointtool.h"
#include "linetool.h"
#include "circletool.h"
#include <QDebug>
#include <QColorDialog>

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
    ui->outlineList->setCurrentRow(idx);
}

void MainWindow::deleteObject(int idx)
{
    delete ui->outlineList->takeItem(idx);
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
        ui->scene->setTool(new LineTool(*ui->scene));
        return;
    }
    if (action == ui->actionCircle) {
        ui->scene->setTool(new CircleTool(*ui->scene));
        return;
    }
}
