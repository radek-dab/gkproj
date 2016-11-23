#ifndef OCTREE_H
#define OCTREE_H

#include "raster.h"
#include <queue>

class Octree
{
public:
    Octree(const Raster &rst, int colors)
        : root(new Node()), nColors(0)
    {
        build(rst);
        reduce(colors);
        computeColors(root);
    }

    ~Octree()
        { clear(root); }

    quint32 map(quint32 pix);
    void map(Raster &rst);

private:
    struct Node
    {
        Node *parent;
        int idx;
        Node *childs[8];
        int nChilds;
        int red, green, blue;
        int nPixs;
        quint32 color;

        /* Root node: */ Node();
        /* Leaf node: */ Node(Node *parent, int idx);

        ~Node();
    };

    struct Comparator
    {
        bool operator ()(const Node *p, const Node *q)
            { return p->nPixs < q->nPixs; }
    };

    Node *root;
    std::priority_queue<Node*, std::vector<Node*>, Comparator> leafs;
    int nColors;

    void insert(quint32 pix);
    void build(const Raster &rst);
    void reduce(int num);
    void computeColors(Node *root);
    void clear(Node *root);
};

inline Octree::Node::Node()
    : parent(NULL), idx(-1), nChilds(0),
      red(0), green(0), blue(0), nPixs(0), color(0)
{
    for (int i = 0; i < 8; i++)
        childs[i] = NULL;
}

inline Octree::Node::Node(Node *parent, int idx)
    : parent(parent), idx(idx), nChilds(0),
      red(0), green(0), blue(0), nPixs(0), color(0)
{
    Q_ASSERT(parent);
    Q_ASSERT(0 <= idx && idx < 8);
    parent->childs[idx] = this;
    parent->nChilds++;
    for (int i = 0; i < 8; i++)
        childs[i] = NULL;
}

inline Octree::Node::~Node()
{
    if (parent) {
        parent->childs[idx] = NULL;
        parent->nChilds--;
    }
}

#endif // OCTREE_H
