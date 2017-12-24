#include "avl.h"

ds::avl::avl() :now_size(0), root(nullptr)
{
}

ds::avl::~avl()
{
    delNode(root);
}

void ds::avl::delNode(storetype p)
{
    if (p->l)
        delNode(p->l);
    if (p->r)
        delNode(p->r);
    delete p;
}

ds::avl::content ds::avl::insert(const elemtype &)
{
    return content();
}

ds::avl::content ds::avl::search(const elemtype & elem)
{
    return content();
}

bool ds::avl::adjust()
{
    return false;
}

bool ds::avl::remove(const elemtype & elem)
{
    return false;
}

bool ds::avl::edit(const elemtype & elem, storetype newvalue)
{
    return false;
}
