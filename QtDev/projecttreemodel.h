#ifndef PROJECTTREEMODEL_H
#define PROJECTTREEMODEL_H

#include <QAbstractItemModel>

namespace blocks
{
  class project;
  class script;
  class library;
}
class projectTreeItem;

class projectTreeModel : public QAbstractItemModel
{
  Q_OBJECT
public:
  projectTreeModel          (blocks::project &data, QObject *parent = 0);
  ~projectTreeModel         ();

  QVariant data             (const QModelIndex &index, int role)                                   const;
  Qt::ItemFlags flags       (const QModelIndex &index)                                             const;
  QVariant headerData       (int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
  QModelIndex index         (int row, int column, const QModelIndex &parent = QModelIndex())       const;
  QModelIndex parent        (const QModelIndex &index)                                             const;

  int rowCount              (const QModelIndex &parent = QModelIndex())                            const;
  int columnCount           (const QModelIndex &parent = QModelIndex())                            const;
private:
  void setupModelDataProject(blocks::project &data, projectTreeItem* parent);
  void setupModelDataScript (blocks::script* s,     projectTreeItem* parent);
  void setupModelDataLibrary(blocks::library &l,    projectTreeItem* parent);

  projectTreeItem* rootItem;
};

#endif // PROJECTTREEMODEL_H
