#ifndef OUTLINELIST_H
#define OUTLINELIST_H

#include "drawable.h"
#include <QListWidget>

class OutlineList : public QListWidget
{
    Q_OBJECT

public:
    OutlineList(QWidget *parent = nullptr)
        : QListWidget(parent) {}
    ~OutlineList() {}

public slots:
    void addObject(Drawable *obj);
    void selectObject(int idx);
};

#endif // OUTLINELIST_H
