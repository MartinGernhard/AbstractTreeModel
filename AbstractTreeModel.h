
//          Copyright Martin Gernhard 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef ABSTRACTTREEMODEL_H
#define ABSTRACTTREEMODEL_H

#include <QAbstractItemModel>
#include <QScopedPointer>
#include <QSharedPointer>

class AbstractTreeNode;

class AbstractTreeModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    typedef QSharedPointer<AbstractTreeNode> NodePtr;

    explicit AbstractTreeModel(QObject *parent = 0);
    virtual ~AbstractTreeModel();

    // AbstractItemModel
    virtual QModelIndex	index (int row, int column, const QModelIndex & parent = QModelIndex()) const;
    virtual QModelIndex	parent (const QModelIndex & index) const;
    virtual int	rowCount (const QModelIndex & parent = QModelIndex()) const;

protected:
    // Call init from the derived constructor!
    void init();
    virtual QList<NodePtr> createRootNodes() = 0;

    class Private;
    QScopedPointer<Private> d;
};

#endif // ABSTRACTTREEMODEL_H
