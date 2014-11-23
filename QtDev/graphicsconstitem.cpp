#include <QBrush>
#include <QTextDocument>
#include <QMessageBox>

#include "blocksGraphicsTypes.h"

#include "graphicsconstitem.h"
#include "constant.h"
#include "exceptions.h"

#include "graphicspinitem.h"

graphicsConstItem::graphicsConstItem(blocks::constant* constant) : graphicsBlockItem(constant)
{
  constantObj = constant;

  QString name = constantObj->constObj().dataToString();

  pinfont = QFont();
  constantValue = new graphicsTextEditItem(name,this);
  constantValue->setTextInteractionFlags(Qt::TextEditable);

  connect(constantValue->document(), SIGNAL(contentsChanged()),
                               this, SLOT  (textChange()));

  connect(constantValue, SIGNAL(editStarted()),
                   this, SLOT  (textEditStarted()));

  connect(constantValue, SIGNAL(editEnded()),
                   this, SLOT  (textEditEnded()));

  QRectF textBox = constantValue->boundingRect();
  textBox.adjust(0,0,blockBorder,blockBorder);
  setRect( textBox );

  constantValue->moveBy(blockBorder/2.0f,blockBorder/2.0f);

  blocks::dataType dt = constantObj->constObj().getDataType();

  graphicsPinItem* pin   = new graphicsPinItem(dt, blocks::output,blockID(),0, this);
  pin->setBrush(QBrush( graphicsBlockItem::getDatatypeColor(dt) ));

  QGraphicsSimpleTextItem* gName = new QGraphicsSimpleTextItem("",this);
  outputPin.push_back(pinInfo(pin,gName));
  recalcBlockGeometry();
}
graphicsConstItem::~graphicsConstItem()
{
}
void graphicsConstItem::recalcBlockGeometry()
{
  QRectF textBox = constantValue->boundingRect();
  textBox.adjust(0,0,blockBorder,blockBorder);
  setRect( textBox );

  float pinYCord = (rect().height() /2) - graphicsPinItem::pinSize/2;

  pinInfo outputPinInfo = outputPin.at(0);
  outputPinInfo.pin->setPos( rect().right(),pinYCord );
  emit blockChanged(this);
}
void graphicsConstItem::textChange()
{
  float widthDiff = (rect().width() - blockBorder) - constantValue->boundingRect().width();
  this->moveBy(widthDiff,0);
  recalcBlockGeometry();
}

void graphicsConstItem::textEditStarted()
{
  lastGoodConstString = constantValue->toPlainText();
}

void graphicsConstItem::textEditEnded()
{
  QString newConst = constantValue->toPlainText();
  try
  {
    constantObj->Obj().stringToData(newConst);
  }
  catch (blocks::conversion_error &e)
  {
    QMessageBox msgBox;
    msgBox.setText(e.what());
    msgBox.exec();
    constantValue->setPlainText(lastGoodConstString);
  }
}

void graphicsConstItem::constantChange(const blocks::constant* const c)
{
  Q_UNUSED(c)
}
void graphicsConstItem::valueChange(const blocks::constant* const c)
{
  Q_UNUSED(c)
}
