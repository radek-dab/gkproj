#include "filtertabwidget.h"
#include "ui_filtertabwidget.h"

FilterTabWidget::FilterTabWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::FilterTabWidget)
{
    ui->setupUi(this);
}

FilterTabWidget::~FilterTabWidget()
{
    delete ui;
}
