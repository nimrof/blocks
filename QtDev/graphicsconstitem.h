#ifndef GRAPHICSCONSTITEM_H
#define GRAPHICSCONSTITEM_H

#include <QObject>

#include "blocksGraphicsTypes.h"

#include "blocks.h"
#include "graphicsblockitem.h"
#include "graphicstextedititem.h"

class graphicsConstItem : public graphicsBlockItem
{
  Q_OBJECT
public:
  enum { Type = blocksConstant };
  graphicsConstItem(blocks::constant* constant);
  virtual ~graphicsConstItem();
  virtual int type() const { return Type; }
private:
  void recalcBlockGeometry();
  blocks::constant*     constantObj;
  graphicsTextEditItem* constantValue;
  QString               lastGoodConstString;
private slots:
  void textEditStarted();
  void textEditEnded();

  void textChange    ();
  void constantChange(const blocks::constant* const c);
  void valueChange   (const blocks::constant* const c);
};

#endif // GRAPHICSCONSTITEM_H
