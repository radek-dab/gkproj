#ifndef OCTREE_H
#define OCTREE_H

#include "raster.h"

class Octree
{
public:
    Octree() : root(new Node()) {}
    ~Octree() { clear(root); }

    void insert(quint32 pix);
    void build(const Raster &rst);

private:
    struct Node
    {
        Node *parent;
        Node *childs[8];
        int depth;
        int r, g, b;
        int count;
        // quint32 color

        Node(Node *parent = NULL)
            : parent(parent),
              depth(parent ? parent->depth+1 : 0),
              r(0), g(0), b(0),
              count(0)
        {
            for (int i = 0; i < 8; i++)
                childs[i] = NULL;
        }
    };

    Node *root;

    void clear(Node *root);
};

#endif // OCTREE_H
