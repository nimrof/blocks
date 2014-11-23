#ifndef GRAPHICSCALLITEM_H
#define GRAPHICSCALLITEM_H

#include "graphicsblockitem.h"

#include "blocksGraphicsTypes.h"

class graphicsCallItem : public graphicsBlockItem
{
public:
  enum { Type = blocksCall };
  graphicsCallItem(blocks::call* callBlock);
  graphicsCallItem(blocks::callDefinition* callDefintion);
  void createGraphicsFromDefinition(blocks::callDefinition* callDefinition);


  virtual int type() const { return Type; }
private:
  blocks::call*              callBlock;
  QGraphicsSimpleTextItem*   graphicsName;
};

#endif // GRAPHICSCALLITEM_H
