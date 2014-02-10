// Boost Software License - Version 1.0 - August 17th, 2003
// 
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

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