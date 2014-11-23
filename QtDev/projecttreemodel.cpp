#include <QStringList>

#include "projecttreemodel.h"

#include "projecttreeitem.h"

#include "project.h"
#include "script.h"
#include "calldefinition.h"

projectTreeModel::projectTreeModel(blocks::project &data, QObject* parent) : QAbstractItemModel(parent)
{
  rootItem = new projectTreeItem();
  setupModelDataProject(data, rootItem);
}
projectTreeModel::~projectTreeModel()
{

}
QVariant projectTreeModel::data(const QModelIndex &index, int role) const
{
  if (!index.isValid())
  {
    return QVariant();
  }
  if (role != Qt::DisplayRole)
  {
    return QVariant();
  }
  projectTreeItem* item = static_cast<projectTreeItem*>(index.internalPointer());

  return item->data(index.column());
}
Qt::ItemFlags projectTreeModel::flags(const QModelIndex &index) const
{
  if (!index.isValid())
  {
    return 0;
  }
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}
QVariant projectTreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  Q_UNUSED(section);
  Q_UNUSED(orientation);
  Q_UNUSED(role);
  return QVariant();
}
QModelIndex projectTreeModel::index(int row, int column, const QModelIndex &parent) const
{
  if (!hasIndex(row, column, parent))
  {
    return QModelIndex();
  }
  projectTreeItem* parentItem;

  if (!parent.isValid())
  {
    parentItem = rootItem;
  }
  else
  {
    parentItem = static_cast<projectTreeItem*>(parent.internalPointer());
  }
  projectTreeItem* childItem = parentItem->child(row);
  if (childItem)
  {
    return createIndex(row, column, childItem);
  }
  else
  {
    return QModelIndex();
  }
}
QModelIndex projectTreeModel::parent(const QModelIndex &index) const
{
  if (!index.isValid())
  {
    return QModelIndex();
  }

  projectTreeItem* childItem = static_cast<projectTreeItem*>(index.internalPointer());
  projectTreeItem* parentItem = childItem->parent();

  if (parentItem == rootItem)
  {
    return QModelIndex();
  }
  return createIndex(parentItem->row(), 0, parentItem);
}
int projectTreeModel::rowCount(const QModelIndex &parent) const
{
  projectTreeItem* parentItem;
  if (parent.column() > 0)
  {
    return 0;
  }
  if (!parent.isValid())
  {
    parentItem = rootItem;
  }
  else
  {
    parentItem = static_cast<projectTreeItem*>(parent.internalPointer());
  }
  return parentItem->childCount();
}
int projectTreeModel::columnCount(const QModelIndex &parent) const
{
  Q_UNUSED(parent);
  return 1;
}
void projectTreeModel::setupModelDataProject(blocks::project &data, projectTreeItem* parent)
{
  projectTreeItem* projectNode = new projectTreeItem(&data, parent);

  parent->appendChild(projectNode);

  setupModelDataLibrary(*data.getProjectLibrary(), projectNode);

  QStringList scripts = data.getScriptList();
  QStringList::const_iterator constIterator;
  for (constIterator = scripts.constBegin(); constIterator != scripts.constEnd(); ++constIterator)
  {
    blocks::script* s = data.getScript(*constIterator);
    setupModelDataScript(s,projectNode);
  }
}
void projectTreeModel::setupModelDataScript(blocks::script* s, projectTreeItem* parent)
{
  projectTreeItem* scriptTreeNode = new projectTreeItem(s,parent);
  parent->appendChild( scriptTreeNode );
}
void projectTreeModel::setupModelDataLibrary(blocks::library &l, projectTreeItem* parent)
{
  projectTreeItem* libraryTreeNode = new projectTreeItem(&l,parent);
  parent->appendChild( libraryTreeNode );

  QStringList definitions = l.getcallDefinitionList();
  QStringList::const_iterator constIterator;
  for (constIterator = definitions.constBegin(); constIterator != definitions.constEnd(); ++constIterator)
  {
    blocks::callDefinition* bd = l.getcallDefinition(*constIterator);
    libraryTreeNode->appendChild( new projectTreeItem(bd,libraryTreeNode) );
  }
}
