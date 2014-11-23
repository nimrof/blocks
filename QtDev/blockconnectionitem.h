#ifndef BLOCKCONNECTIONITEM_H
#define BLOCKCONNECTIONITEM_H

#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QObject>

#include "pindefinition.h"
#include "blocks.h"

#include "blocksGraphicsTypes.h"

class graphicsBlockItem;

class blockConnectionItem : public QObject, public QGraphicsPathItem
{
  Q_OBJECT
public:
  enum {Type = blocksConnection};
  blockConnectionItem             (const graphicsBlockItem* sb, const blocks::itemID sp, const graphicsBlockItem* tb, const blocks::itemID tp);
  virtual int type                () const { return Type; }
  void updateSourceCoordinates    ();
  void updateTargetCoordinates    ();
  virtual QPainterPath shape      () const;
  void removeInScript             ();

  blocks::itemID getSourceBlockID () const;
  blocks::itemID getTargetBlockID () const;
  blocks::itemID getSourcePinIndex() const;
  blocks::itemID getTargetPinIndex() const;
public slots:
  void sourceBlockMoved           (const blocks::itemID blockID, const QPoint newPos, const QPoint newRelativePos);
  void sourceBlockChanged         (const graphicsBlockItem* block);
  void targetBlockMoved           (const blocks::itemID blockID, const QPoint newPos, const QPoint newRelativePos);
  void targetBlockChanged         (const graphicsBlockItem* block);
  void connectedBlockRemoved      (const graphicsBlockItem* block);
private:
  QPointF getPinCoordinate        (const graphicsBlockItem* block, const size_t pinIndex, const blocks::pinType pt);
  void redrawPath                 ();
  virtual QVariant itemChange     (GraphicsItemChange change, const QVariant &value);

  const graphicsBlockItem* sourceBlock;
  const graphicsBlockItem* targetBlock;
  blocks::itemID           sourcePin;
  blocks::itemID           targetPin;

  QPainterPath             painter;

  QPointF                  start;
  QPointF                  end;
};

#endif // BLOCKCONNECTIONITEM_H
