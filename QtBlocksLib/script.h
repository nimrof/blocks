#ifndef SCRIPT_H
#define SCRIPT_H

#include <map>

#include "blocks.h"

#include <QObject>
#include <QString>
#include <QDomDocument>
#include <QPoint>

namespace blocks
{

class script : public QObject
{
  Q_OBJECT
public:
  script                             (blocks::project* parent);
  QString      getName               ();
  void         saveToXML             (QDomElement &node, const int version)                                    const;
  void         readFromXML           (const QDomElement node, const int version, const project& parentProject);
  itemID       getNumBlocks          ()                                                                        const;
  block*       getBlock              (const itemID id);
  const block* getBlock              (const itemID id) const;

  void         addConnection         (const itemID sourceBlockID, const itemID sourcePinIndex, const itemID targetBlockID, const itemID targetPinIndex);
  void         addCallBlock          (call* newCall, const itemID ID = -1);
  void         addConstant           (constant* newConstant, const itemID ID = -1);
  void         removeConnection      (const itemID sourceBlockID, const itemID sourcePinIndex, const itemID targetBlockID, const itemID targetPinIndex);
  void         removeBlock           (const itemID blockID);
  void         createBlock           (const QString methodeName, const QPoint position, const itemID ID = -1);
private slots:
  void         blockevent_moved      (const itemID blockID, const QPoint newPositon, const QPoint movement);
signals:
  void         blockMoved            (const blocks::itemID blockID, const QPoint newPosition, const QPoint movement);
  void         blockRemoved          (const blocks::itemID blockID);
  void         connectionRemoved     (const blocks::itemID sourceBlockID, const blocks::itemID sourcePinIndex, const blocks::itemID targetBlockID, const blocks::itemID targetPinIndex);
  void         blockCreated          (const blocks::itemID blockID);
  void         connectionCreated     (const blocks::itemID sourceBlockID, const blocks::itemID sourcePinIndex, const blocks::itemID targetBlockID, const blocks::itemID targetPinIndex);
private:
  void         readCallsFromXML      (const QDomElement node, const int version, const project& parentProject);
  void         readConstantsFromXML  (const QDomElement node, const int version);
  void         readConnectionsFromXML(const QDomElement node, const int version);

  itemID       getFreeID             ();
  bool         isIDFree              (const itemID id);

  QString name;
  std::map<itemID, block*> blockMap;
  blocks::project* parentProject;
};

}

#endif // SCRIPT_H
