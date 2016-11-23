#include "octree.h"
#include <QDebug>
#include <QElapsedTimer>

quint32 Octree::map(quint32 pix)
{
    Q_ASSERT(root);
    Node *p = root;

    for (quint8 bit = 1 << 7; bit; bit >>= 1) {
        int i = !!(Raster::red(pix) & bit) << 2
              | !!(Raster::green(pix) & bit) << 1
              | !!(Raster::blue(pix) & bit);

        if (!p->childs[i])
            break;

        p = p->childs[i];
    }

    return p->color;
}

void Octree::map(Raster &rst)
{
    QElapsedTimer timer;
    timer.start();

    quint32 *end = rst.pixels() + rst.w*rst.h;
    for (quint32 *pix = rst.pixels(); pix != end; pix++)
        *pix = map(*pix);

    qDebug() << "Mapped raster with octree in"
             << timer.nsecsElapsed()/1e6 << "ms";
}

void Octree::insert(quint32 pix)
{
    Q_ASSERT(root);
    Node *p = root;

    for (quint8 bit = 1 << 7; bit; bit >>= 1) {
        int i = !!(Raster::red(pix) & bit) << 2
              | !!(Raster::green(pix) & bit) << 1
              | !!(Raster::blue(pix) & bit);

        if (!p->childs[i])
            new Node(p, i);

        p = p->childs[i];
    }

    p->red += Raster::red(pix);
    p->green += Raster:: green(pix);
    p->blue += Raster::blue(pix);
    if (++p->nPixs == 1) {
        leafs.push(p);
        nColors++;
    }
}

void Octree::build(const Raster &rst)
{
    QElapsedTimer timer;
    timer.start();

    const quint32 *end = rst.pixels() + rst.w*rst.h;
    for (const quint32 *pix = rst.pixels(); pix != end; pix++)
        insert(*pix);

    qDebug() << "Built octree of" << nColors << "colors"
             << "in" << timer.nsecsElapsed()/1e6 << "ms";
}

void Octree::reduce(int num)
{
    QElapsedTimer timer;
    timer.start();

    while (nColors > num) {
        Node *p = leafs.top();
        Node *q = p->parent;
        leafs.pop();

        // Reduction
        if (q->nPixs > 0)
            nColors--;

        q->red += p->red;
        q->green += p->green;
        q->blue += p->blue;
        q->nPixs += p->nPixs;

        delete p;
        if (q->nChilds == 0)
            leafs.push(q);
    }

    qDebug() << "Reduced octree to" << nColors << "colors"
             << "in" << timer.nsecsElapsed()/1e6 << "ms";
}

void Octree::computeColors(Node *root)
{
    if (!root)
        return;

    if (root->nPixs > 0)
        root->color = Raster::makeColor(root->red   / root->nPixs,
                                        root->green / root->nPixs,
                                        root->blue  / root->nPixs);

    for (int i = 0; i < 8; i++)
        computeColors(root->childs[i]);
}

void Octree::clear(Node *root)
{
    if (!root)
        return;

    for (int i = 0; i < 8; i++)
        clear(root->childs[i]);

    delete root;
}
