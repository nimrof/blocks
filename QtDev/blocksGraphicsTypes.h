#ifndef BLOCKSGRAPHICSTYPES_H
#define BLOCKSGRAPHICSTYPES_H

#include <QGraphicsItem>

enum blocksGraphicTypes
{
  blocksPin        = QGraphicsItem::UserType + 1,
  blocksConnection = QGraphicsItem::UserType + 2,
  blocksCall       = QGraphicsItem::UserType + 3,
  blocksConstant   = QGraphicsItem::UserType + 4
};

#endif // BLOCKSGRAPHICSTYPES_H
