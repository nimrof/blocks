#include <algorithm>
#include <stdexcept>

#include <QPainter>
#include <QRectF>
#include <QSizeF>
#include <QString>
#include <QGraphicsSimpleTextItem>
#include <QBrush>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>

#include "calldefinition.h"
#include "graphicsblockitem.h"
#include "block.h"

#include "graphicspinitem.h"

graphicsBlockItem::graphicsBlockItem(blocks::block *block) : blockBorder( 10.0f )
{
  if(block != NULL)
  {
    ID = block->getID();
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFlag(QGraphicsItem::ItemIsSelectable);
  }
}
graphicsBlockItem::~graphicsBlockItem()
{
  emit blockRemoved(this);
}
QPointF graphicsBlockItem::getPinSceneCoordinate(blocks::pinType pt, size_t pinIndex) const
{
  QGraphicsEllipseItem* pin;

  switch(pt)
  {
    case blocks::input:
      pin = inputPin.at(pinIndex).pin;
      break;
    case blocks::output:
      pin = outputPin.at(pinIndex).pin;
      break;
  }

  QPointF pos;
  pos = pin->pos();
  pos.setY(pos.ry() + graphicsPinItem::pinSize/2);
  pos.setX(pos.rx() + graphicsPinItem::pinSize/2);

  return this->mapToScene(pos);
}
QColor graphicsBlockItem::getDatatypeColor(const blocks::dataType dt)
{
  switch(dt)
  {
    case blocks::BOOLEAN:  return QColor(  Qt::green);
    case blocks::INT_8:    return QColor(   Qt::blue);
    case blocks::INT_16:   return QColor(   Qt::blue);
    case blocks::INT_32:   return QColor(   Qt::blue);
    case blocks::INT_64:   return QColor(   Qt::blue);
    case blocks::UINT_8:   return QColor(   Qt::blue);
    case blocks::UINT_16:  return QColor(   Qt::blue);
    case blocks::UINT_32:  return QColor(   Qt::blue);
    case blocks::UINT_64:  return QColor(   Qt::blue);
    case blocks::FLOAT_32: return QColor( 255,127, 0);//orange
    case blocks::FLOAT_64: return QColor( 255,127, 0);//orange
    case blocks::ARRAY:    return QColor( Qt::yellow);//base color..TODO
    case blocks::STRUCT:   return QColor( Qt::yellow);
    case blocks::STRING:   return QColor(Qt::magenta);
    default:
      return QColor(Qt::black);
  }
}
blocks::itemID graphicsBlockItem::blockID() const
{
  return ID;
}
void graphicsBlockItem::highlightPins(const blocks::dataType dt, const blocks::pinType pt)
{
  std::vector<pinInfo>::iterator it;
  std::vector<pinInfo>* pVector;

  switch (pt)
  {
    case blocks::input:
      pVector = &inputPin;
      break;
    case blocks::output:
      pVector = &outputPin;
      break;
  }

  for ( it=pVector->begin() ; it < pVector->end(); it++ )
  {
    if( it->pin->getDatatype() == dt )
    {
      it->pin->setHighlight(true);
    }
  }
}
void graphicsBlockItem::UnhighlightPins()
{
  std::vector<pinInfo>::iterator it;

  for ( it=inputPin.begin() ; it < inputPin.end(); it++ )
  {
    it->pin->setHighlight(false);
  }

  for ( it=outputPin.begin() ; it < outputPin.end(); it++ )
  {
    it->pin->setHighlight(false);
  }
}

QVariant graphicsBlockItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
  if (change == ItemPositionChange && scene())
  {
    OldPos = pos();
    // value is the new position.
    QPointF newPos = value.toPointF();
    QRectF rect = scene()->sceneRect();
    if (!rect.contains(newPos))
    {
      // Keep the item inside the scene rect.
      newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
      newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));

      return newPos;
    }
  }
  else if (change == ItemPositionHasChanged && scene())
  {
    emit blockMoved(blockID(),pos().toPoint(), QPointF( pos()-OldPos).toPoint());
  }
  else if (change == ItemSelectedChange && scene())
  {
    if(isSelected())
    {
      setBrush(QBrush(QColor(Qt::white)));
    }
    else
    {
      setBrush(QBrush(QColor(Qt::red)));
    }
  }

  return QGraphicsItem::itemChange(change, value);
}
