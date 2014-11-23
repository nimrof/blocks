#include <QFontMetrics>
#include <QBrush>

#include "graphicscallitem.h"
#include "call.h"
#include "calldefinition.h"

#include "graphicspinitem.h"

graphicsCallItem::graphicsCallItem(blocks::call* callBlock) : graphicsBlockItem(callBlock)
{
  this->callBlock = callBlock;
  blocks::callDefinition* callDefinition = callBlock->getcallDefinition();
  createGraphicsFromDefinition(callDefinition);
}

graphicsCallItem::graphicsCallItem(blocks::callDefinition* callDefintion) : graphicsBlockItem(0)
{
  createGraphicsFromDefinition(callDefintion);
}

void graphicsCallItem::createGraphicsFromDefinition(blocks::callDefinition* callDefinition)
{
  QString name = callDefinition->getName();

  unsigned int numInput  = callDefinition->getNumPinsOfType(blocks::input);
  unsigned int numOutput = callDefinition->getNumPinsOfType(blocks::output);

  unsigned int numMaxIOPin = std::max(numInput,numOutput);
  pinfont = QFont();
  graphicsName = new QGraphicsSimpleTextItem(name,this);

  QRectF textBox = graphicsName->boundingRect();

  QFontMetrics fm = QFontMetrics(pinfont);

  int maxInputTextWidth = 0;
  for(unsigned int i = 0; i < numInput; i++)
  {
    QString name = callDefinition->getPin(blocks::input,i)->getName();
    int Width = fm.width(name);
    maxInputTextWidth = std::max(maxInputTextWidth,Width);
  }

  int maxOutputTextWidth = 0;
  for(unsigned int i = 0; i < numOutput; i++)
  {
    QString name = callDefinition->getPin(blocks::output,i)->getName();
    int Width = fm.width(name);
    maxOutputTextWidth = std::max(maxOutputTextWidth,Width);
  }

  int PinHeight = std::max(fm.height(),(int)graphicsPinItem::pinSize);

  QRectF mainBox = textBox;
  mainBox.setWidth( maxOutputTextWidth + maxInputTextWidth + 10 );
  mainBox.adjust(-blockBorder,-5,blockBorder,blockBorder);
  mainBox.adjust(0,0,0,numMaxIOPin* PinHeight);

  setRect(mainBox);

  inputPin.resize(numInput);
  QPointF boxPos = QPointF(mainBox.left() -graphicsPinItem::pinSize, textBox.bottom() + blockBorder);
  for(unsigned int i = 0; i < numInput; i++)
  {
    blocks::dataType dt = callDefinition->getPin(blocks::input,i)->getDataType();
    QString name        = callDefinition->getPin(blocks::input,i)->getName();

    graphicsPinItem* pin = new graphicsPinItem(dt, blocks::input,this->blockID(),i, this);
    pin->setPos(boxPos);
    pin->setBrush(QBrush( graphicsBlockItem::getDatatypeColor(dt) ));

    QGraphicsSimpleTextItem* gName = new QGraphicsSimpleTextItem(name,this);
    gName->setPos(boxPos.rx()+blockBorder,boxPos.y()-7);
    inputPin[i] = pinInfo(pin,gName);
    boxPos.setY(boxPos.ry() + PinHeight);
  }

  boxPos.setX(mainBox.right());
  boxPos.setY(textBox.bottom());

  outputPin.resize(numOutput);
  boxPos.setY(boxPos.ry() + 10);

  for(unsigned int i = 0; i < numOutput; i++)
  {
    blocks::dataType dt = callDefinition->getPin(blocks::output,i)->getDataType();
    QString name        = callDefinition->getPin(blocks::output,i)->getName();
    int nameWidth       = fm.width(name);

    graphicsPinItem* pin = new graphicsPinItem(dt, blocks::output,this->blockID(),i, this);
    pin->setPos(boxPos);
    pin->setBrush(QBrush( graphicsBlockItem::getDatatypeColor(dt) ));

    QGraphicsSimpleTextItem* gName = new QGraphicsSimpleTextItem(name,this);
    gName->setPos(rect().width()-(nameWidth+15),boxPos.ry()-7);

    outputPin[i] = pinInfo(pin,gName);
    boxPos.setY(boxPos.ry() + graphicsPinItem::pinSize*4);
  }
}
