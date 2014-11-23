#include "graphicspinitem.h"

#include <QGraphicsEllipseItem>
#include <QBrush>

graphicsPinItem::graphicsPinItem( const blocks::dataType dt, const blocks::pinType pt, const blocks::itemID blockID, const blocks::itemID pinIndex, QGraphicsItem* parent ) : QGraphicsEllipseItem(parent)
{
  setRect(0, 0, (float)pinSize , (float)pinSize);

  dataType         = dt;
  pinType          = pt;
  this->blockID    = blockID;
  this->pinIndex   = pinIndex;
}

void graphicsPinItem::setHighlight(bool highlightActive)
{
  float multiplier = 2.0;
  if(highlightActive)
  {
    float newPinSize = pinSize*multiplier;
    setRect(-newPinSize/2.0,-newPinSize/2.0,newPinSize+pinSize, newPinSize+pinSize);
  }
  else
  {
    setRect(0,0,pinSize,pinSize);
  }
}

blocks::dataType graphicsPinItem::getDatatype()
{
  return dataType;
}
blocks::itemID  graphicsPinItem::getPinIndex()
{
  return pinIndex;
}

blocks::pinType graphicsPinItem::getPinType()
{
  return pinType;
}

blocks::itemID graphicsPinItem::getBlockID()
{
  return blockID;
}
