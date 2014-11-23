#include "script.h"
#include "call.h"
#include "constant.h"
#include "calldefinition.h"

#include "scripteditor.h"
#include "scripteditorundocommands.h"

#include "pin.h"
#include <QDropEvent>
#include <QGraphicsItem>
#include <QMimeData>

#include "blocksGraphicsTypes.h"
#include "graphicspinitem.h"

ScriptEditor::ScriptEditor(QWidget* parent) : QGraphicsView(parent)
{
  setAlignment(Qt::AlignLeft | Qt::AlignTop);
  setScene(&scene);
  setRenderHint(QPainter::Antialiasing,true);
  setAcceptDrops(true);
  this->setDragMode(RubberBandDrag);
  curScript   = 0;
  selectedPin = 0;
}
void ScriptEditor::LoadScript(blocks::script& script)
{
  curScript = &script;

  connect(curScript, SIGNAL(blockMoved                       (const blocks::itemID, const QPoint, const QPoint)),
                            this, SLOT(scriptEvent_blockMoved(const blocks::itemID, const QPoint, const QPoint)));

  connect(curScript, SIGNAL(blockRemoved(const blocks::itemID)),
                            this, SLOT(scriptEvent_blockRemoved(const blocks::itemID)));
  connect(curScript, SIGNAL(blockCreated(const blocks::itemID)),
                            this, SLOT(scriptEvent_blockCreated(const blocks::itemID)));

  connect(curScript, SIGNAL(connectionCreated( const blocks::itemID, const blocks::itemID, const blocks::itemID, const blocks::itemID)),
                            this, SLOT(scriptEvent_connectionCreated(const blocks::itemID, const blocks::itemID, const blocks::itemID, const blocks::itemID)));
  connect(curScript, SIGNAL(connectionRemoved( const blocks::itemID, const blocks::itemID, const blocks::itemID, const blocks::itemID)),
                            this, SLOT(scriptEvent_connectionRemoved(const blocks::itemID, const blocks::itemID, const blocks::itemID, const blocks::itemID)));

  LoadScriptCallBlocks(script);
  LoadScriptBlockConnections(script);
}
void ScriptEditor::keyPressEvent  (QKeyEvent* event)
{
  QGraphicsView::keyPressEvent(event);
  if ( event->matches(QKeySequence::Delete) )
  {
    QList<QGraphicsItem*> selectedList = scene.selectedItems();

    for (int i = 0; i < selectedList.size(); ++i)
    {
      QGraphicsItem* item = selectedList.at(i);
      int type = item->type();

      switch(type)
      {
        case blockConnectionItem::Type:
        {
          blockConnectionItem* connection = qgraphicsitem_cast<blockConnectionItem*>(item);
          removeConnection(connection);
          break;
        }
        case graphicsCallItem::Type:
        {
          graphicsCallItem* call = qgraphicsitem_cast<graphicsCallItem*>(item);
          removeBlock(call);
          break;
        }
        case graphicsConstItem::Type:
        {
          graphicsConstItem* contant = qgraphicsitem_cast<graphicsConstItem*>(item);
          break;
        }
      }
    }
  }
  else if( event->matches(QKeySequence::Undo) )
  {
    undoStack.undo();
  }
  else if( event->matches(QKeySequence::Find))
  {
    undoStack.push(new moveBlockCommand(curScript, 7,QPoint(400,200),QPoint(400,300)) );
  }
}
void ScriptEditor::keyReleaseEvent(QKeyEvent* event)
{
  QGraphicsView::keyReleaseEvent(event);
}
void ScriptEditor::mouseMoveEvent(QMouseEvent* event)
{
  QGraphicsView::mouseMoveEvent(event);
}
void ScriptEditor::mousePressEvent(QMouseEvent* event)
{
  if(event->button() == Qt::LeftButton)
  {
    QGraphicsItem* item = itemAt(event->pos());
    if(item)
    {
      if(item->type() == blocksPin)
      {
        graphicsPinItem* pinAtPos = qgraphicsitem_cast<graphicsPinItem*>(item);

        if(selectedPin == 0)
        {
          selectedPin = pinAtPos;
          blocks::pinType targetPintype = selectedPin->getPinType() == blocks::input ? blocks::output : blocks::input;

          std::map<blocks::itemID, graphicsBlockItem*>::iterator it;
          for ( it = scriptItemGraphicItemMap.begin(); it != scriptItemGraphicItemMap.end(); it++ )
          {
            it->second->highlightPins(selectedPin->getDatatype(), targetPintype);
          }
        }
        else
        {
          blocks::itemID startBlock;
          blocks::itemID startPinIndex;
          blocks::itemID endBlock;
          blocks::itemID endPinIndex;

          if( pinAtPos->getPinType() == blocks::input )
          {
            startBlock    = selectedPin->getBlockID();
            startPinIndex = selectedPin->getPinIndex();
            endBlock      = pinAtPos->getBlockID();
            endPinIndex   = pinAtPos->getPinIndex();
          }
          else
          {
            startBlock    = pinAtPos->getBlockID();
            startPinIndex = pinAtPos->getPinIndex();
            endBlock      = selectedPin->getBlockID();
            endPinIndex   = selectedPin->getPinIndex();
          }

          curScript->addConnection(startBlock,startPinIndex,endBlock,endPinIndex);
        }
      }
    }
    else if(selectedPin != 0)
    {
      selectedPin = 0;
      std::map<blocks::itemID, graphicsBlockItem*>::iterator it;
      for ( it = scriptItemGraphicItemMap.begin(); it != scriptItemGraphicItemMap.end(); it++ )
      {
        it->second->UnhighlightPins();
      }
    }
  }
  QGraphicsView::mousePressEvent(event);
}
void ScriptEditor::mouseReleaseEvent(QMouseEvent* event)
{
  QGraphicsView::mouseReleaseEvent(event);
}
void ScriptEditor::LoadScriptCallBlocks(blocks::script& script)
{
  size_t numBlock = script.getNumBlocks();

  for(size_t i = 0; i < numBlock; i++)
  {
    blocks::block* b           = script.getBlock(i);
    QPointF blockPos           = b->pos();

    if(b->type() == blocks::block::callBlock)
    {
      blocks::call* callBlock = static_cast<blocks::call*>(b);

      graphicsCallItem* graphicBlock = new graphicsCallItem(callBlock);
      graphicBlock->setFlag(QGraphicsItem::ItemIsMovable,true);

      graphicBlock->setPos(blockPos);
      scene.addItem( graphicBlock );

      scriptItemGraphicItemMap.insert( std::make_pair(callBlock->getID(),graphicBlock) );
      connect(graphicBlock, SIGNAL(blockMoved    (const blocks::itemID, const QPoint, const QPoint)),
                      this, SLOT  (userMovedBlock(const blocks::itemID, const QPoint, const QPoint)));
    }
    else if(b->type() == blocks::block::constantBlock)
    {
      blocks::constant* constBlock = static_cast<blocks::constant*>(b);

      graphicsConstItem* graphicBlock = new graphicsConstItem(constBlock);
      graphicBlock->setFlag(QGraphicsItem::ItemIsMovable,true);

      graphicBlock->setPos(blockPos);
      scene.addItem( graphicBlock );

      scriptItemGraphicItemMap.insert( std::make_pair(constBlock->getID(),graphicBlock) );
      connect(graphicBlock, SIGNAL(blockMoved    (const blocks::itemID, const QPoint, const QPoint)),
                      this, SLOT  (userMovedBlock(const blocks::itemID, const QPoint, const QPoint)));
    }
  }
}
void ScriptEditor::LoadScriptBlockConnections(blocks::script& script)
{
  size_t numBlock = script.getNumBlocks();

  for(size_t i = 0; i < numBlock; i++)
  {
    blocks::block* b = script.getBlock(i);

    for (unsigned int pi = 0; pi < b->getNumPinsOfType(blocks::output); pi++)
    {
      //Add connections after all blocks is added, so we have a graphic item on all the blocks
      blocks::pin* pin      = b->getPinAt(pi,blocks::output);
      size_t sourcePinIndex = b->getPinIndex(pin,blocks::output);

      for (unsigned int ci = 0; ci < pin->numConnections(); ci++)
      {
        blocks::pin*   targetPin   = pin->getConnectionTarget(ci);
        blocks::block* targetBlock = targetPin->getParentBlock();
        size_t targetPinIndex      = targetBlock->getPinIndex(targetPin,blocks::input);

        graphicsBlockItem* sourceGraphBlock = scriptItemGraphicItemMap[i];
        graphicsBlockItem* targetGraphBlock = scriptItemGraphicItemMap[targetBlock->getID()];

        blockConnectionItem* connection = new blockConnectionItem(sourceGraphBlock,sourcePinIndex,targetGraphBlock,targetPinIndex);
        connections.push_back(connection);
        scene.addItem(connection);
      }
    }
  }
}
void ScriptEditor::dragEnterEvent(QDragEnterEvent* event)
{
  if (event->mimeData()->hasFormat("application/x-blocks/call/link") && curScript)
  {
    if (event->source() != this)
    {
      event->setDropAction(Qt::MoveAction);
      event->accept();
    }
    else
    {
      event->acceptProposedAction();
    }
  }
  else
  {
    event->ignore();
  }
}
void ScriptEditor::dragMoveEvent(QDragMoveEvent* event)
{

}
void ScriptEditor::dropEvent(QDropEvent* event)
{
  if (event->mimeData()->hasFormat("application/x-blocks/call/link") && curScript)
  {
    if (event->source() != this)
    {
      event->accept();
      QString callBlockLink;
      QByteArray itemData = event->mimeData()->data("application/x-blocks/call/link");
      QDataStream dataStream(&itemData, QIODevice::ReadOnly);
      dataStream >> callBlockLink;
      curScript->createBlock(callBlockLink,event->pos());
    }
    else
    {
      event->ignore();
    }
  }
  else
  {
    event->ignore();
  }
}
void ScriptEditor::removeBlock(graphicsBlockItem* block)
{
  blocks::itemID blockID = block->blockID();

  undoStack.push(new blockDeleteCommand(curScript, curScript->getBlock(blockID) ) );
}
void ScriptEditor::removeConnection(blockConnectionItem* connection)
{
  undoStack.push(new connectionRemoveCommand(curScript, connection) );
}
void ScriptEditor::scriptEvent_blockMoved(const blocks::itemID blockID, const QPoint newPosition, const QPoint movement)
{
  Q_UNUSED(movement)
  graphicsBlockItem* block = scriptItemGraphicItemMap[blockID];

  if(block->pos() != newPosition)
  {
    block->setPos(newPosition);
  }
}
void ScriptEditor::scriptEvent_blockRemoved(const blocks::itemID blockID)
{
  graphicsBlockItem* block = scriptItemGraphicItemMap[blockID];
  scriptItemGraphicItemMap.erase(blockID);
  scene.removeItem( block );
  delete block;
}
void ScriptEditor::scriptEvent_connectionRemoved(const blocks::itemID sourceBlockID, const blocks::itemID sourcePinIndex, const blocks::itemID targetBlockID, const blocks::itemID targetPinIndex)
{
  std::vector<blockConnectionItem*>::iterator it;

  for ( it = connections.begin() ; it < connections.end(); it++ )
  {
    if( ( (*it)->getSourceBlockID()  == sourceBlockID  ) &&
        ( (*it)->getTargetBlockID()  == targetBlockID  ) &&
        ( (*it)->getSourcePinIndex() == sourcePinIndex ) &&
        ( (*it)->getTargetPinIndex() == targetPinIndex ) )
    {
      blockConnectionItem* connection = *it;
      connections.erase(it);
      scene.removeItem(connection);
      delete connection;
    }
  }
}
void ScriptEditor::scriptEvent_blockCreated(const blocks::itemID blockID)
{
  blocks::block* b = curScript->getBlock(blockID);
  QPointF blockPos = b->pos();

  graphicsBlockItem* graphicBlock = 0;
  if(b->type() == blocks::block::callBlock)
  {
    blocks::call* callBlock = static_cast<blocks::call*>(b);
    graphicBlock = new graphicsCallItem(callBlock);
  }
  else if(b->type() == blocks::block::constantBlock)
  {
    blocks::constant* constBlock = static_cast<blocks::constant*>(b);
    graphicBlock = new graphicsConstItem(constBlock);
  }

  graphicBlock->setFlag(QGraphicsItem::ItemIsMovable,true);

  graphicBlock->setPos(blockPos);
  scene.addItem( graphicBlock );

  scriptItemGraphicItemMap.insert( std::make_pair(blockID,graphicBlock) );

  connect(graphicBlock, SIGNAL(blockMoved()), this, SLOT  (blockMoved()));
}
void ScriptEditor::scriptEvent_connectionCreated(const blocks::itemID sourceBlockID, const blocks::itemID sourcePinIndex, const blocks::itemID targetBlockID, const blocks::itemID targetPinIndex)
{
  graphicsBlockItem* sourceGraphBlock = scriptItemGraphicItemMap[sourceBlockID];
  graphicsBlockItem* targetGraphBlock = scriptItemGraphicItemMap[targetBlockID];

  blockConnectionItem* connection = new blockConnectionItem(sourceGraphBlock,sourcePinIndex,targetGraphBlock,targetPinIndex);
  connections.push_back(connection);
  scene.addItem(connection);
}
void ScriptEditor::userMovedBlock(const blocks::itemID blockID, QPoint newPosition, QPoint newRelativePosition)
{
  Q_UNUSED(newRelativePosition)
  QPoint curPos = curScript->getBlock(blockID)->pos();
  QPoint newPos = newPosition;
  if(newPos != curScript->getBlock(blockID)->pos())
  {
    undoStack.push(new moveBlockCommand(curScript, blockID,curPos,newPos) );
  }
}
