#include "mainwindow.h"
#include <QApplication>

#if DEBUG_MATRIX
#include "models/matrix.h"
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

#if DEBUG_MATRIX
    QList<int> sizes = {3, 5, 7};
    foreach (int size, sizes) {
        Matrix mat(size);
        mat.setToGaussianBlur();
    }
#endif

    return a.exec();
}
