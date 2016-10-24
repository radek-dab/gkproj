#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

private slots:
    void on_actionForegroundColor_triggered();
    void on_actionBackgroundColor_triggered();
    void on_actionGrid_triggered();
    void on_scene_resized();

    void setTool();

private:
    Ui::MainWindow *ui;
    QActionGroup *toolGroup;
    QLabel *sizeLabel;
};

#endif // MAINWINDOW_H
