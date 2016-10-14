#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "raster.h"
#include <QDebug>
#include <QColorDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    sizeLabel(new QLabel)
{
    ui->setupUi(this);
    ui->statusBar->addWidget(sizeLabel);

    for (int i = 1; i <= 10; i++)
        ui->listWidget->addItem(QString("Circle %1").arg(i));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionForegroundColor_triggered()
{
    QColor color = QColorDialog::getColor(foregroundColor);
    if (!color.isValid()) return;
    ui->rasterWidget->setForegroundColor(color);
    qDebug() << "Foreground color:" << foregroundColor;
}

void MainWindow::on_actionBackgroundColor_triggered()
{
    QColor color = QColorDialog::getColor(backgroundColor);
    if (!color.isValid()) return;
    ui->rasterWidget->setBackgroundColor(color);
    qDebug() << "Foreground color:" << backgroundColor;
}

void MainWindow::on_rasterWidget_resized()
{
    QSize size = ui->rasterWidget->size();
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
