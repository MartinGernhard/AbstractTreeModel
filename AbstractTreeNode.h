
//          Copyright Martin Gernhard 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ABSTRACTTREENODE_H
#define ABSTRACTTREENODE_H

#include <QList>
#include <QScopedPointer>
#include <QSharedPointer>

class AbstractTreeNode
{
public:
    typedef QSharedPointer<AbstractTreeNode> NodePtr;

    AbstractTreeNode(AbstractTreeNode * parent, int row);
    virtual ~AbstractTreeNode();

    QList<NodePtr> childNodes() const;
    AbstractTreeNode * parentNode() const;
    int row() const;
protected:
    // Call init from the derived constructor!
    void init();
    virtual QList<NodePtr> createChildNodes() = 0;

    class Private;
    QScopedPointer<Private> d;
};

#endif // ABSTRACTTREENODE_H
