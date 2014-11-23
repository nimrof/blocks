#ifndef GRAPHICSBLOCKITEM_H
#define GRAPHICSBLOCKITEM_H

#include <map>

#include <vector>
#include <QRectF>
#include <QFont>
#include <QObject>
#include <QFocusEvent>

#include <QGraphicsItem>
#include "pindefinition.h"

#include "blocks.h"

#include "graphicspinitem.h"

struct pinInfo
{
  pinInfo()                                                  {pin= 0;  name=0;}
  pinInfo(graphicsPinItem* gPin, QGraphicsSimpleTextItem* n) {pin=gPin;name=n;}
  graphicsPinItem*         pin;
  QGraphicsSimpleTextItem* name;
};

class graphicsBlockItem : public QObject, public QGraphicsRectItem
{
  Q_OBJECT
public:
  graphicsBlockItem                       (blocks::block* block);
  virtual           ~graphicsBlockItem    ();
  QPointF           getPinSceneCoordinate (blocks::pinType pt, size_t pinIndex)                        const;
  static QColor     getDatatypeColor      (const blocks::dataType dt);
  blocks::itemID    blockID               ()                                                           const;
  void              highlightPins         (const blocks::dataType dt, const blocks::pinType pt);
  void              UnhighlightPins       ();
signals:
  void              blockMoved            (const blocks::itemID blockID, const QPoint newPos, const QPoint newRelativePos);
  void              blockChanged          (const graphicsBlockItem* block);
  void              blockRemoved          (const graphicsBlockItem* block);
protected:
  QPointF                                 OldPos;//Should try to remove this when time
  blocks::itemID                          ID;
  QFont                                   pinfont;
  const float                             blockBorder;
  std::vector<pinInfo>                    inputPin;
  std::vector<pinInfo>                    outputPin;
private:
  virtual QVariant  itemChange            (GraphicsItemChange change, const QVariant &value);
};

#endif // GRAPHICSBLOCKITEM_H
