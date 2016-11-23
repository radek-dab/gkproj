#include "octree.h"

void Octree::insert(quint32 pix)
{
    Q_ASSERT(root);
    Node *p = root;

    for (quint8 bit = 1 << 7; bit; bit >>= 1) {
        int i = !!(Raster::red(pix) & bit) << 2
              | !!(Raster::green(pix) & bit) << 1
              | !!(Raster::blue(pix) & bit);

        if (!p->childs[i])
            p->childs[i] = new Node(p);

        p = p->childs[i];
    }

    p->r += Raster::red(pix);
    p->g += Raster:: green(pix);
    p->b += Raster::blue(pix);
    p->count++;
}

void Octree::build(const Raster &rst)
{
    const quint32 *end = rst.pixels() + rst.w*rst.h;
    for (const quint32 *pix = rst.pixels(); pix != end; pix++)
        insert(*pix);
}

void Octree::clear(Node *root)
{
    if (!root)
        return;

    for (int i = 0; i < 8; i++)
        clear(root->childs[i]);

    delete root;
}
