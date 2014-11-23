#include "scripteditorundocommands.h"
#include "script.h"
#include "block.h"
#include "call.h"
#include "calldefinition.h"

moveBlockCommand::moveBlockCommand(blocks::script* script, const blocks::itemID ID, const QPoint &oldPos, const QPoint &newPos, QUndoCommand *parent)
{
  Q_UNUSED(parent)
  this->script = script;
  blockID      = ID;
  this->oldPos = oldPos;
  this->newPos = newPos;
}
void moveBlockCommand::undo()
{
  script->getBlock(blockID)->setPos(oldPos);
}
void moveBlockCommand::redo()
{
  script->getBlock(blockID)->setPos(newPos);
}
bool moveBlockCommand::mergeWith(const QUndoCommand* command)
{
  moveBlockCommand* undoMove = (moveBlockCommand*)command;

  if(blockID ==  undoMove->blockID)
  {
    newPos = undoMove->newPos;
    return true;
  }
  else
  {
    return false;
  }
}
blockDeleteCommand::blockDeleteCommand(blocks::script* script, const blocks::block* block, QUndoCommand* parent)
{
  Q_UNUSED(parent)
  this->script    = script;
  blockID         = block->getID();
  pos             = block->pos();

  switch ( block->type() )
  {
    case blocks::block::callBlock:
    {
      blocks::call*     callblock = (blocks::call*)block;
      blockDefinition = callblock->getcallDefinition()->getFullName();
      break;
    }
    case blocks::block::constantBlock:
    {
      blocks::constant* constblock = (blocks::constant*)block;
      break;
    }
  }
}
void blockDeleteCommand::undo()
{
  script->createBlock(blockDefinition,pos,blockID);
}
void blockDeleteCommand::redo()
{
  script->removeBlock(blockID);
}
blockAddCommand::blockAddCommand(blocks::script* script, const blocks::block* block, QUndoCommand* parent)
{
}
void blockAddCommand::undo()
{
  script->removeBlock(blockID);
}
void blockAddCommand::redo()
{
}
connectionAddCommand::connectionAddCommand(blocks::script* script, const blockConnectionItem* connection, QUndoCommand* parent)
{
  Q_UNUSED(parent)
  this->script  = script;
  sourceBlockID = connection->getSourceBlockID();
  targetBlockID = connection->getTargetBlockID();
  sourcePin     = connection->getSourcePinIndex();
  targetPin     = connection->getTargetPinIndex();
}
void connectionAddCommand::undo()
{
  script->removeConnection(sourceBlockID, sourcePin, targetBlockID, targetPin);
}
void connectionAddCommand::redo()
{
  script->addConnection(sourceBlockID, sourcePin, targetBlockID, targetPin);
}
connectionRemoveCommand::connectionRemoveCommand(blocks::script* script, const blockConnectionItem* connection, QUndoCommand* parent)
{
  Q_UNUSED(parent)
  this->script  = script;
  sourceBlockID = connection->getSourceBlockID();
  targetBlockID = connection->getTargetBlockID();
  sourcePin     = connection->getSourcePinIndex();
  targetPin     = connection->getTargetPinIndex();
};
void connectionRemoveCommand::undo()
{
  script->addConnection(sourceBlockID, sourcePin, targetBlockID, targetPin);
}
void connectionRemoveCommand::redo()
{
  script->removeConnection(sourceBlockID, sourcePin, targetBlockID, targetPin);
}
