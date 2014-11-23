#include <script.h>
#include <project.h>
#include <library.h>
#include <calldefinition.h>

#include "projecttreeitem.h"

projectTreeItem::projectTreeItem()
{
  type = root;
  pData = 0;
  parentItem = 0;
}
projectTreeItem::projectTreeItem(blocks::script* s, projectTreeItem* parent)
{
  type = script;
  pData = s;
  parentItem = parent;
}
projectTreeItem::projectTreeItem(blocks::project* p, projectTreeItem* parent)
{
  type = project;
  pData = p;
  parentItem = parent;
}
projectTreeItem::projectTreeItem(blocks::library* l, projectTreeItem* parent)
{
  type = library;
  pData = l;
  parentItem = parent;
}
projectTreeItem::projectTreeItem(blocks::callDefinition* bd, projectTreeItem* parent)
{
  type = callDefinition;
  pData = bd;
  parentItem = parent;
}
void projectTreeItem::appendChild(projectTreeItem* child)
{
  childItems.append(child);
}
projectTreeItem* projectTreeItem::child(int row)
{
  return childItems.value(row);
}
int projectTreeItem::childCount() const
{
  return childItems.count();
}
QVariant projectTreeItem::data(int column) const
{
  Q_UNUSED(column);

  switch(type)
  {
    case script:
      {
        blocks::script* pScript= static_cast<blocks::script*>(pData);
        return pScript->getName();
      }
      break;
    case project:
      {
        blocks::project* pProject = static_cast<blocks::project*>(pData);
        return pProject->getName();
      }
      break;
    case library:
      {
        blocks::library* pLibrary = static_cast<blocks::library*>(pData);
        return pLibrary->getName();
      }
      break;
    case callDefinition:
      {
        blocks::callDefinition* pcallDefinition = static_cast<blocks::callDefinition*>(pData);
        return pcallDefinition->getName();
      }
      break;
    default:
      return "Error";
  }
}
projectTreeItem* projectTreeItem::parent()
{
  return parentItem;
}
int projectTreeItem::row() const
{
  if (parentItem)
      return parentItem->childItems.indexOf(const_cast<projectTreeItem*>(this));

  return 0;
}
itemType projectTreeItem::getType()
{
  return type;
}
void* projectTreeItem::getRawData()
{
  return pData;
}
