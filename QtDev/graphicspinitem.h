#ifndef GRAPHICSPINITEM_H
#define GRAPHICSPINITEM_H

#include <QGraphicsEllipseItem>

#include "blocksGraphicsTypes.h"
#include "blocks.h"
#include "blockvariable.h"
#include "pindefinition.h"

class graphicsPinItem : public QGraphicsEllipseItem
{
public:
  enum { Type = blocksPin };
  graphicsPinItem( const blocks::dataType dt, const blocks::pinType pt, const blocks::itemID blockID, const blocks::itemID pinIndex , QGraphicsItem * parent = 0);
  void setHighlight(bool highlightActive);
  virtual int type() const { return Type; }

  blocks::dataType getDatatype();
  blocks::itemID   getPinIndex();
  blocks::pinType  getPinType();
  blocks::itemID   getBlockID();

  const static int pinSize = 5;
private:
  blocks::dataType dataType;
  blocks::pinType  pinType;
  blocks::itemID   blockID;
  blocks::itemID   pinIndex;
};

#endif // GRAPHICSPINITEM_H
