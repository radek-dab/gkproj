#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "griddialog.h"
#include <QDebug>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    sizeLabel(new QLabel)
{
    ui->setupUi(this);
    ui->statusBar->addWidget(sizeLabel);
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::on_actionGrid_triggered()
{
    GridDialog dialog(this);
    dialog.exec();
}

void MainWindow::on_scene_resized()
{
    QSize size = ui->scene->size();
    QString text = QString("%1x%2").arg(size.width()).arg(size.height());
    sizeLabel->setText(text);
}

void MainWindow::chooseShape()
{
    QAction *shapes[] = {
        ui->actionPoint,
        ui->actionLine,
        ui->actionCircle,
        NULL
    };
    QAction *chosenShape = qobject_cast<QAction*>(sender());

    if (!chosenShape->isChecked())
        return;

    for (QAction **p = shapes; *p; p++) {
        QAction *shape = *p;
        if (shape != chosenShape) {
            shape->setChecked(false);
        }
    }
}
