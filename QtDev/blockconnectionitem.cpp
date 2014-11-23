#include "blockconnectionitem.h"
#include "graphicsblockitem.h"

#include <QPen>
#include <QGraphicsScene>

blockConnectionItem::blockConnectionItem(const graphicsBlockItem* sb, const blocks::itemID sp, const graphicsBlockItem* tb, const blocks::itemID tp)
{
  setFlag(QGraphicsItem::ItemIsSelectable,true);

  QPen newPen = pen();
  newPen.setWidth(2);
  setPen(newPen);

  sourceBlock = sb;
  sourcePin   = sp;

  targetBlock = tb;
  targetPin   = tp;

  connect(sb, SIGNAL(blockMoved(const blocks::itemID, const QPoint, const QPoint)),
                     this, SLOT(sourceBlockMoved(const blocks::itemID, const QPoint, const QPoint)));
  connect(tb, SIGNAL(blockMoved(const blocks::itemID, const QPoint, const QPoint)),
                     this, SLOT(targetBlockMoved(const blocks::itemID, const QPoint, const QPoint)));

  connect(sb, SIGNAL(blockChanged(const graphicsBlockItem*)),
                     this, SLOT(sourceBlockChanged(const graphicsBlockItem*)));
  connect(tb, SIGNAL(blockChanged(const graphicsBlockItem*)),
                     this, SLOT(targetBlockChanged(const graphicsBlockItem*)));

  connect(sb, SIGNAL(blockRemoved(const graphicsBlockItem*)),
                     this, SLOT(connectedBlockRemoved(const graphicsBlockItem*)));
  connect(tb, SIGNAL(blockRemoved(const graphicsBlockItem*)),
                     this, SLOT(connectedBlockRemoved(const graphicsBlockItem*)));

  updateSourceCoordinates();
  updateTargetCoordinates();
  redrawPath();
  setZValue(-1);
}
void blockConnectionItem::updateSourceCoordinates()
{
  start = getPinCoordinate(sourceBlock, sourcePin, blocks::output);
}
void blockConnectionItem::updateTargetCoordinates()
{
  end   = getPinCoordinate(targetBlock, targetPin, blocks::input);
}
QPainterPath blockConnectionItem::shape() const
{
  QPainterPathStroker pathStroker;
  pathStroker.setWidth(20);
  return pathStroker.createStroke(path());
}
void blockConnectionItem::removeInScript()
{

}
blocks::itemID blockConnectionItem::getSourceBlockID() const
{
  return sourceBlock->blockID();
}
blocks::itemID blockConnectionItem::getTargetBlockID() const
{
  return targetBlock->blockID();
}
blocks::itemID blockConnectionItem::getSourcePinIndex() const
{
  return sourcePin;
}
blocks::itemID blockConnectionItem::getTargetPinIndex() const
{
  return targetPin;
}

void blockConnectionItem::sourceBlockChanged(const graphicsBlockItem* block)
{
  Q_UNUSED(block)
  updateSourceCoordinates();
  redrawPath();
}
void blockConnectionItem::targetBlockChanged(const graphicsBlockItem* block)
{
  Q_UNUSED(block)
  updateTargetCoordinates();
  redrawPath();
}
void blockConnectionItem::sourceBlockMoved(const blocks::itemID blockID, const QPoint newPos, const QPoint newRelativePos)
{
  Q_UNUSED(blockID)
  Q_UNUSED(newPos)

  start = start + newRelativePos;
  redrawPath();
}
void blockConnectionItem::targetBlockMoved(const blocks::itemID blockID, const QPoint newPos, const QPoint newRelativePos)
{
  Q_UNUSED(blockID)
  Q_UNUSED(newPos)

  end = end + newRelativePos;
  redrawPath();
}
void blockConnectionItem::connectedBlockRemoved(const graphicsBlockItem* block)
{
  Q_UNUSED(block)
  if(scene())
  {
    scene()->removeItem(this);
  }
  delete this;
}
QPointF blockConnectionItem::getPinCoordinate(const graphicsBlockItem* block, const size_t pinIndex, const blocks::pinType pt)
{
  return block->getPinSceneCoordinate(pt, pinIndex);
}
void blockConnectionItem::redrawPath()
{
  this->setPos(start);
  QPointF relStart;
  QPointF relEnd = end - start;

  qreal deltaX          = (relStart.rx() - relEnd.rx()) / 2.0f;
  QPointF controlPoint1 = relStart;
  QPointF controlPoint2 = relEnd;

  if(relStart.rx() < relEnd.rx())
  {
    controlPoint1.rx() = relEnd.rx()   + deltaX;
    controlPoint2.rx() = relStart.rx() - deltaX;
  }
  else
  {
    controlPoint1.rx() = relStart.rx() + deltaX;
    controlPoint2.rx() = relEnd.rx()   - deltaX;
  }
  painter = QPainterPath();
  painter.cubicTo(controlPoint1,controlPoint2,relEnd);
  setPath(painter);
}
QVariant blockConnectionItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
  if (change == QGraphicsItem::ItemSelectedChange && scene())
  {
    if(isSelected())
    {
      QPen newPen = pen();
      newPen.setColor( QColor(Qt::black) );
      setPen(newPen);
    }
    else
    {
      QPen newPen = pen();
      newPen.setColor( QColor(Qt::red) );
      setPen(newPen);
    }
  }
  return QGraphicsItem::itemChange(change, value);
}
