#include "outlinelist.h"

void OutlineList::addObject(Drawable *obj)
{
    addItem(obj->name());
    setCurrentRow(count()-1);
}

void OutlineList::selectObject(int idx)
{
    setCurrentRow(idx);
}
