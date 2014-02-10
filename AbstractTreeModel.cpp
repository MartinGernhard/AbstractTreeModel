
//          Copyright Martin Gernhard 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "AbstractTreeModel.h"
#include "AbstractTreeNode.h"

// This class is in the spirit of the python classes at
// http://www.hardcoded.net/articles/using_qtreeview_with_qabstractitemmodel.htm
//
// This is a very simple "read-only" model that does not support fine-grained updates.
// Instead, it is expected that every method of the derived model class works like this:
// void DerivedModel::addData( ... ) {
//   beginResetModel(); // Signal to views that the model data will be invalidated.
//   ... do stuff to the underlying data.
//   init(); // Re-generate all nodes.
//   endResetModel(); // Force all views to re-read everything from the model.
// }
//
// Some notes:
// * The (invisible) root of a tree model is an invalid QModelIndex.
// * Only the first column has children.
// * We are storing raw pointers to data as internalPointer.
//   This is okay, since users must never use invalid QModelIndexes anyway.
// * internalPointer() points to instances of AbstractTreeNode, not to the
//   actual implementation-specific data. Instead, the concrete class derived
//   from AbstractTreeNode needs to hold a reference to the actual data.
// * Derived classes have to call init() at some point during construction,
//   when they have initialised themselves enough for getRootNodes to be called.
//   init() can not be called from this class' constructor since at the time
//   the "this" pointer is of type AbstractTreeModel* and createRootNodes()
//   is pure virtual.

class AbstractTreeModel::Private
{
public:
    QList<NodePtr> rootNodes;
};

AbstractTreeModel::AbstractTreeModel(QObject *parent) :
    QAbstractItemModel(parent), d(new Private())
{
}

AbstractTreeModel::~AbstractTreeModel()
{
}

void AbstractTreeModel::init()
{
    d->rootNodes = createRootNodes();
}

QModelIndex AbstractTreeModel::index(int row, int column, const QModelIndex & parent) const
{
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    if(!parent.isValid()) {
        // Return QModelIndex to a first level node.
        return createIndex(row, column, d->rootNodes[row].data());
    } else {
        AbstractTreeNode * parentNode = static_cast<AbstractTreeNode*>(parent.internalPointer());
        return createIndex(row, column, parentNode->childNodes()[row].data());
    }
}

QModelIndex AbstractTreeModel::parent(const QModelIndex & index) const
{
    if(!index.isValid())
        return QModelIndex();

    AbstractTreeNode * node = static_cast<AbstractTreeNode*>(index.internalPointer());
    AbstractTreeNode * parentNode = node->parentNode();
    if(parentNode == NULL) {
        // Parent of first level node is root.
        return QModelIndex();
    } else {
        // Only the first column (0) has children.
        return createIndex(parentNode->row(), 0, parentNode);
    }
}

int AbstractTreeModel::rowCount(const QModelIndex & parent) const
{
    if(!parent.isValid()) {
        return d->rootNodes.size();
    } else {
        // Only the first column (0) has children.
        if(parent.column() != 0)
            return 0;

        AbstractTreeNode * node = static_cast<AbstractTreeNode*>(parent.internalPointer());
        return node->childNodes().size();
    }
}
