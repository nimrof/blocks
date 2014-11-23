#ifndef SCRIPTEDITORUNDOCOMMANDS_H
#define SCRIPTEDITORUNDOCOMMANDS_H

#include <QUndoCommand>
#include <QPointF>

#include "blocks.h"
#include "blockconnectionitem.h"

class moveBlockCommand : public QUndoCommand
{
public:
  moveBlockCommand(blocks::script* script, const blocks::itemID ID, const QPoint &oldPos, const QPoint &newPos, QUndoCommand* parent = 0);
  void undo();
  void redo();
  bool mergeWith(const QUndoCommand* command);
  int  id ()const {return 1;}

  blocks::script* script;
  blocks::itemID  blockID;
  QPoint          oldPos;
  QPoint          newPos;
};

class blockDeleteCommand : public QUndoCommand
{
public:
  blockDeleteCommand(blocks::script* script, const blocks::block* block, QUndoCommand* parent = 0);
  void undo();
  void redo();
private:
  blocks::script* script;
  QString         blockDefinition;
  blocks::itemID  blockID;
  QPoint          pos;
};

class blockAddCommand  : public QUndoCommand
{
public:
  blockAddCommand(blocks::script* script, const blocks::block* block, QUndoCommand* parent = 0);
  void undo();
  void redo();
private:
  blocks::script* script;
  QString         blockDefinition;
  blocks::itemID  blockID;
  QPoint          pos;
};

class connectionAddCommand : public QUndoCommand
{
public:
  connectionAddCommand(blocks::script* script, const blockConnectionItem* connection, QUndoCommand* parent = 0);
  void undo();
  void redo();
private:
  blocks::script* script;
  blocks::itemID  sourceBlockID;
  blocks::itemID  targetBlockID;
  blocks::itemID  sourcePin;
  blocks::itemID  targetPin;
};

class connectionRemoveCommand  : public QUndoCommand
{
public:
  connectionRemoveCommand(blocks::script* script, const blockConnectionItem* connection, QUndoCommand* parent = 0);
  void undo();
  void redo();
private:
  blocks::script* script;
  blocks::itemID  sourceBlockID;
  blocks::itemID  targetBlockID;
  blocks::itemID  sourcePin;
  blocks::itemID  targetPin;
};

#endif // SCRIPTEDITORUNDOCOMMANDS_H
