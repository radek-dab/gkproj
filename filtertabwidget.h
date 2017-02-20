#ifndef FILTERTABWIDGET_H
#define FILTERTABWIDGET_H

#include <QTabWidget>

namespace Ui {
class FilterTabWidget;
}

class FilterTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit FilterTabWidget(QWidget *parent = 0);
    ~FilterTabWidget();

private:
    Ui::FilterTabWidget *ui;
};

#endif // FILTERTABWIDGET_H
