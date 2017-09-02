#ifndef GRIDDIALOG_H
#define GRIDDIALOG_H

#include "models/grid.h"
#include <QDialog>

namespace Ui {
class GridDialog;
}

class GridDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GridDialog(QWidget *parent = 0);
    ~GridDialog();

    Grid grid() const;
    void setGrid(const Grid &grid);

private:
    Ui::GridDialog *ui;
};

#endif // GRIDDIALOG_H
