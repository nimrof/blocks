#ifndef SCRIPTEDITOR_H
#define SCRIPTEDITOR_H

#include <map>
#include <vector>

#include <QGraphicsView>
#include <QUndoStack>

#include "graphicscallitem.h"
#include "graphicsconstitem.h"
#include "blockconnectionitem.h"

#include "blocks.h"


class ScriptEditor : public QGraphicsView
{
  Q_OBJECT
public:
  explicit ScriptEditor             (QWidget* parent = 0);
  void LoadScript                   (blocks::script& script);
protected:
  virtual void keyPressEvent        (QKeyEvent* event);
  virtual void keyReleaseEvent      (QKeyEvent* event);

  virtual void  mouseMoveEvent      (QMouseEvent* event);
  virtual void  mousePressEvent     (QMouseEvent* event);
  virtual void  mouseReleaseEvent   (QMouseEvent* event);

  void dragEnterEvent               (QDragEnterEvent* event);
  void dragMoveEvent                (QDragMoveEvent*  event);
  void dropEvent                    (QDropEvent*      event);
private slots:
  void userMovedBlock               (const blocks::itemID blockID, const QPoint newPosition, const QPoint newRelativePosition);
  void scriptEvent_blockMoved       (const blocks::itemID blockID, const QPoint newPosition, const QPoint movement);
  void scriptEvent_blockRemoved     (const blocks::itemID blockID);
  void scriptEvent_connectionRemoved(const blocks::itemID sourceBlockID, const blocks::itemID sourcePinIndex, const blocks::itemID targetBlockID, const blocks::itemID targetPinIndex);
  void scriptEvent_blockCreated     (const blocks::itemID blockID);
  void scriptEvent_connectionCreated(const blocks::itemID sourceBlockID, const blocks::itemID sourcePinIndex, const blocks::itemID targetBlockID, const blocks::itemID targetPinIndex);
private:
  void LoadScriptCallBlocks         (blocks::script& script);
  void LoadScriptBlockConnections   (blocks::script& script);
  void LoadScriptConstBlocks        (blocks::script& script);
  void LoadScriptConstConnections   (blocks::script& script);

  void removeBlock                  (graphicsBlockItem* block);
  void removeConnection             (blockConnectionItem* connection);
//  void addBlock()
//  void addConnection()
  graphicsPinItem* selectedPin;

  QUndoStack       undoStack;

  QGraphicsScene   scene;
  blocks::script*  curScript;

  std::map<blocks::itemID, graphicsBlockItem*> scriptItemGraphicItemMap;//TODO://bad bad name :(
  std::vector<blockConnectionItem*>            connections;
};

#endif // SCRIPTEDITOR_H
