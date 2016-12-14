#ifndef CLIPWINDOW_H
#define CLIPWINDOW_H

#include "window.h"

class ClipWindow : public Window
{
public:
    ClipWindow(QRect rect, quint32 color)
        : Window(rect, color) {}

    QLine clip(const QLine &line);
};

#endif // CLIPWINDOW_H
