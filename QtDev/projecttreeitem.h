#ifndef PROJECTTREEITEM_H
#define PROJECTTREEITEM_H

#include <QList>
#include <QVariant>

#include "blocks.h"

enum itemType
{
  root,
  project,
  library,
  callDefinition,
  script
};

class projectTreeItem
{
public:
  projectTreeItem();
  projectTreeItem(blocks::script*          s, projectTreeItem *parent);
  projectTreeItem(blocks::project*         p, projectTreeItem *parent);
  projectTreeItem(blocks::library*         l, projectTreeItem *parent);
  projectTreeItem(blocks::callDefinition* bd, projectTreeItem *parent);

  ~projectTreeItem();

  void appendChild(projectTreeItem* child);

  projectTreeItem* child  (int row);
  int childCount          () const;
  QVariant data           (int column) const;
  int row                 () const;
  projectTreeItem* parent ();
  itemType getType        ();
  void*    getRawData     ();
private:
  itemType type;
  QList<projectTreeItem*> childItems;
  projectTreeItem*        parentItem;

  void* pData;//Lurt???
};

#endif // PROJECTTREEITEM_H
