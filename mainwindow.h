#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QColor>

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
    void chooseShape();

private slots:
    void on_actionForegroundColor_triggered();
    void on_actionBackgroundColor_triggered();
    void on_rasterWidget_resized();

private:
    Ui::MainWindow *ui;
    QLabel *sizeLabel;
    QColor foregroundColor;
    QColor backgroundColor;
};

#endif // MAINWINDOW_H
