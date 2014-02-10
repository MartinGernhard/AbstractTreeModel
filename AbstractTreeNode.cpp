
//          Copyright Martin Gernhard 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "AbstractTreeNode.h"

// This class is in the spirit of the python classes at
// http://www.hardcoded.net/articles/using_qtreeview_with_qabstractitemmodel.htm
//
// Some notes:
// * This class is really only necessary because Qt expects two things of models:
//     A) Parent nodes know their children.
//     B) Child nodes know their parent.
//   Depending on the actual data structures, B) might not be true, thus we need
//   to wrap all data nodes in AbstractTreeNode.
// * Every AbstractTreeNode has ownership of its childNodes but not of its parentNode.
// * Derived classes have to call init() at some point during construction,
//   when they have initialised themselves enough for getChildren to be called.
//   init() can not be called from this class' constructor since at the time
//   the "this" pointer is of type AbstractTreeNode* and createChildNodes()
//   is pure virtual.


class AbstractTreeNode::Private
{
public:
    AbstractTreeNode * parentNode;
    int row;
    QList<NodePtr> childNodes;
};

AbstractTreeNode::AbstractTreeNode(AbstractTreeNode * parent, int row) : d(new Private())
{
    d->parentNode = parent;
    d->row = row;
}

AbstractTreeNode::~AbstractTreeNode()
{
}

QList<AbstractTreeNode::NodePtr> AbstractTreeNode::childNodes() const
{
    return d->childNodes;
}

AbstractTreeNode * AbstractTreeNode::parentNode() const
{
    return d->parentNode;
}

int AbstractTreeNode::row() const
{
    return d->row;
}

void AbstractTreeNode::init()
{
    d->childNodes = createChildNodes();
}
