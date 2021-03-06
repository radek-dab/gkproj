#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "drawables/drawable.h"
#include <QMainWindow>
#include <QActionGroup>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void addObject(Drawable *obj);
    void selectObject(int idx);
    void reorderObject(int from, int to);
    void deleteObject(int idx);
    void renameObject(int idx, const QString &name);
    void toggleFilterWindow();
    void updateStatus();

signals:
    void objectSelected(int idx);

private slots:
    void on_actionForegroundColor_triggered();
    void on_actionBackgroundColor_triggered();
    void on_actionConfigureGrid_triggered();
    void setTool();
    void on_actionImage_triggered();
    void on_actionObject3D_triggered();
    void setFill();
    void on_fillPatternToolButton_clicked();
    void on_reduceSlider_valueChanged(int value);
    void setChannel();
    void setShade();
    void on_normalsCheckBox_toggled(bool checked);
    void on_normalsToolButton_clicked();
    void on_actionComb_triggered();
    void on_actionLenna_triggered();

private:
    Ui::MainWindow *ui;
    QActionGroup *toolGroup;
    QLabel *statusLabel;

    void addImage(const QString &filename);
};

#endif // MAINWINDOW_H
