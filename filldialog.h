#ifndef FILLDIALOG_H
#define FILLDIALOG_H

#include "filltool.h"
#include <QDialog>

namespace Ui {
class FillDialog;
}

class FillDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FillDialog(QWidget *parent = 0);
    ~FillDialog();

    FillTool * getTool(Scene &scene);

private:
    Ui::FillDialog *ui;
};

#endif // FILLDIALOG_H
