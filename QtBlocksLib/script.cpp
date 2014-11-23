#include <stdexcept>

#include <QStringList>
#include <QString>

#include "exceptions.h"
#include "calldefinition.h"
#include "call.h"
#include "project.h"
#include "pin.h"
#include "constant.h"
#include "script.h"

namespace blocks
{

script::script(project *parent)
{
  parentProject = parent;
}
void script::saveToXML(QDomElement &node, const int version) const
{
  node.setAttribute("name", name);

  QDomElement callsNode = node.ownerDocument().createElement("calls");
  QDomElement constantsNode = node.ownerDocument().createElement("constants");
  QDomElement connectionsNode = node.ownerDocument().createElement("connections");

  node.appendChild(callsNode);
  node.appendChild(constantsNode);
  node.appendChild(connectionsNode);

  std::map<itemID, block*>::const_iterator it;
  for ( it = blockMap.begin(); it != blockMap.end(); it++ )
  {
    block const* b = it->second;
    switch( b->type() )
    {
      case block::callBlock:
        {
          call const* callBlock = static_cast<call const*>(b);

          QDomElement callNode = callsNode.ownerDocument().createElement("call");
          callsNode.appendChild(callNode);

          callNode.setAttribute("methode", callBlock->getcallDefinition()->getFullName() );
          callNode.setAttribute("id"     , b->getID() );
          callNode.setAttribute("xpos"   , b->pos().x() );
          callNode.setAttribute("ypos"   , b->pos().y() );
        }
        break;
      case block::constantBlock:
        {
          constant const* constBlock = static_cast<constant const*>(b);

          QDomElement constNode = constantsNode.ownerDocument().createElement("constant");
          constantsNode.appendChild(constNode);

          constNode.setAttribute("dataType", blockVariable::datatypeToString( constBlock->constObj().getDataType() ) );
          constNode.setAttribute("value"   , constBlock->constObj().dataToString() );

          constNode.setAttribute("id"      , b->getID() );
          constNode.setAttribute("xpos"    , b->pos().x() );
          constNode.setAttribute("ypos"    , b->pos().y() );
        }
        break;
    }

    //printout coonnections

    unsigned int numOutputPins = b->getNumPinsOfType(output);
    for(unsigned int i = 0; i < numOutputPins; i++)
    {

      pin const* p = b->getPinAt(i,output);
      size_t numConnections = p->numConnections();

      for(unsigned int c = 0; c < numConnections; c++)
      {
        pin const* pt = p->getConnectionTarget(c);

        itemID sourceBlock = b->getID();
        itemID outputPin   = i;
        itemID targetBlock = pt->getParentBlock()->getID();
        itemID targetPin   = pt->pinIndex();

        QDomElement connetionNode = connectionsNode.ownerDocument().createElement("connection");
        connectionsNode.appendChild(connetionNode);

        connetionNode.setAttribute("sourceblock", sourceBlock  );
        connetionNode.setAttribute("outputPin"  , outputPin );

        connetionNode.setAttribute("targetBlock", targetBlock );
        connetionNode.setAttribute("targetPin"  , targetPin );
      }
    }
  }
}
void script::readFromXML(const QDomElement node, const int version, const project &parentProject)
{
  if(node.tagName() != "script")
  {
    throw "internal error: node with tagname != 'script' was sendt to library parser";
  }

  name = node.attribute("name");

  QDomElement callsNode       = node.firstChildElement("calls");
  QDomElement constantsNode   = node.firstChildElement("constants");//opt
  QDomElement connectionsNode = node.firstChildElement("connections");

  readCallsFromXML( callsNode, version, parentProject);
  readConstantsFromXML( constantsNode, version);
  readConnectionsFromXML( connectionsNode, version);
}
QString script::getName()
{
  return name;
}
itemID script::getNumBlocks() const
{
  return blockMap.size();
}
block* script::getBlock(const itemID index)
{
  std::map<int, block*>::iterator it;
  it = blockMap.find(index);
  if( it != blockMap.end() )
  {
    return it->second;
  }
  else
  {
    throw unknownBlockID_error(index,__func__);
  }
}
const block* script::getBlock(const itemID index) const
{
  std::map<int, block*>::const_iterator it;
  it = blockMap.find(index);
  if( it != blockMap.end() )
  {
    return it->second;
  }
  else
  {
    throw unknownBlockID_error(index,__func__);
  }
}
void script::readCallsFromXML(const QDomElement node, const int version, const project& parentProject)
{
  Q_UNUSED(version);

  QDomElement child = node.firstChildElement("call");

  while (!child.isNull())
  {
    QString methodeName = child.attribute("methode");

    bool dummy;
    unsigned int callId = child.attribute("id").toInt(&dummy);
    unsigned int xpos   = child.attribute("xpos").toInt(&dummy);
    unsigned int ypos   = child.attribute("ypos").toInt(&dummy);

    createBlock(methodeName, QPoint(xpos,ypos), callId);

    child = child.nextSiblingElement("call");
  }
}
void script::readConnectionsFromXML(const QDomElement node, const int version )
{
  Q_UNUSED(version);

  QDomElement child = node.firstChildElement("connection");//connection from call
  while (!child.isNull())
  {
    bool notInUse;
    unsigned int sourceBlockID = child.attribute( "sourceblock" ).toInt( &notInUse );
    unsigned int outputPin     = child.attribute( "outputPin"   ).toInt( &notInUse );
    unsigned int targetBlockID = child.attribute( "targetBlock" ).toInt( &notInUse );
    unsigned int targetPin     = child.attribute( "targetPin"   ).toInt( &notInUse );

    if( getBlock(sourceBlockID) == NULL )
    {
      throw xml_logic_error(QString("Failed to find outputblock with id='%1' in script: '%2' ")
                            .arg(sourceBlockID)
                            .arg(name));
    }

    if( getBlock(targetBlockID) == NULL )
    {
      throw xml_logic_error(QString("Failed to find targetblock with id='%1' in script: '%2' ")
                            .arg(targetBlockID)
                            .arg(name));
    }

    addConnection(sourceBlockID, outputPin, targetBlockID, targetPin);

    child = child.nextSiblingElement("connection");
  }
}
void script::readConstantsFromXML  (const QDomElement node, const int version)
{
  Q_UNUSED(version);

  if( !node.isNull() )//optional node
  {
    QDomElement child = node.firstChildElement("constant");
    while (!child.isNull())
    {
      bool notInUse;
      unsigned int constantID  = child.attribute(       "id" ).toInt( &notInUse );
      QString      rawDatatype = child.attribute( "dataType" );
      QString      rawvalue    = child.attribute(    "value" );
      unsigned int xpos        = child.attribute(     "xpos" ).toInt( &notInUse );
      unsigned int ypos        = child.attribute(     "ypos" ).toInt( &notInUse );

      constant* newConst;
      try
      {
        newConst = new constant(constantID, rawDatatype, rawvalue);
      }
      catch (xml_logic_error& e)
      {
        throw xml_logic_error(QString("Reading of datatype with value with id:%1 failed").arg(constantID));
      }
      catch (conversion_error& e)
      {
        throw xml_logic_error(QString("Reading of constant value with id:%1 failed").arg(constantID),e.what());
      }

      newConst->setPos(QPoint(xpos,ypos));

      blockMap.insert( std::make_pair(constantID, newConst) );
      child = child.nextSiblingElement("constant");
    }
  }
}
void script::addConnection(const itemID sourceBlockID, const itemID sourcePinIndex, const itemID targetBlockID, const itemID targetPinIndex)
{
  std::map<unsigned int, block*>::iterator blockIt;

  block* sourceBlock;
  block* targetBlock;
  try
  {
    sourceBlock = getBlock(sourceBlockID);
    targetBlock = getBlock(targetBlockID);
  }
  catch(QStringExceptions e)
  {
    throw;
  }

  pin* sourcePin;
  pin* targetPin;
  try
  {
    sourcePin = sourceBlock->getPinAt(sourcePinIndex, output);
  }
  catch (std::out_of_range e)
  {
    throw unknownPinIndex_error(sourcePinIndex,QString("Looking in block with ID:%1").arg(sourcePinIndex));
  }

  try
  {
    targetPin = targetBlock->getPinAt(targetPinIndex, input);
  }
  catch (std::out_of_range e)
  {
    throw unknownPinIndex_error(targetPinIndex,QString("Looking in block with ID:%1").arg(targetPinIndex));
  }

  sourcePin->addConnectionTo(targetPin);
  targetPin->addConnectionTo(sourcePin);

  emit connectionCreated(sourceBlockID, sourcePinIndex, targetBlockID, targetPinIndex);
}
void script::addCallBlock(call* newCall, itemID ID)
{
   unsigned int newID;

   if(ID < 0)
   {
     if( isIDFree(ID) )
     {
       //ID is free to use
       newID = (unsigned int)ID;
     }
     else
     {
       throw blockIDNotFree_error(ID, __func__);
     }
   }
   else
   {
     newID = getFreeID();
   }

   blockMap.insert( std::make_pair(newID, newCall) );
   emit blockCreated(newID);
}
void script::addConstant (constant* newConstant, itemID ID)
{
  unsigned int newID;

  if(ID < 0)
  {
    if( blockMap.find(ID) == blockMap.end() )
    {
      //ID is free to use
      newID = (unsigned int)ID;
    }
    else
    {
      throw blockIDNotFree_error(ID, __func__);
    }
  }
  else
  {
    newID = getFreeID();
  }

  blockMap.insert( std::make_pair(newID, newConstant) );
  emit blockCreated(newID);
}
void script::removeConnection(const itemID sourceBlockID, const itemID sourcePinIndex, const itemID targetBlockID, const itemID targetPinIndex)
{
  block* sourceBlock = getBlock(sourceBlockID);
  pin* sourcePin = sourceBlock->getPinAt(sourcePinIndex,output);

  block* targetBlock = getBlock(targetBlockID);
  pin* targetPin = targetBlock->getPinAt(targetPinIndex,input);

  sourcePin->removeConnectionTo(targetPin);
  emit connectionRemoved(sourceBlockID,sourcePinIndex, targetBlockID, targetPinIndex);
}
void script::removeBlock(const itemID blockID)
{
  block* blockToBeRemoved = getBlock(blockID);

  if( blockToBeRemoved == NULL )
  {
    throw unknownBlockID_error(blockID, __func__);
  }

  //check for connections to/from block (should move this?)
  size_t numPin = blockToBeRemoved->getNumPinsOfType(input);
  for (size_t i = 0; i < numPin; i++)
  {
    pin* p = blockToBeRemoved->getPinAt(i, input);
    size_t numConnections = p->numConnections();
    for (size_t c = 0; c < numConnections; c++)
    {

      p->removeConnectionTo( p->getConnectionTarget(0) );
    }
  }

  numPin = blockToBeRemoved->getNumPinsOfType(output);
  for (size_t i = 0; i < numPin; i++)
  {
    pin* p = blockToBeRemoved->getPinAt(i, output);
    size_t numConnections = p->numConnections();
    for (size_t c = 0; c < numConnections; c++)
    {
      unsigned int sourceBlockID = blockToBeRemoved->getID();
      unsigned int sourcePinIndex = i;
      unsigned int targetBlockID  = p->getParentBlock()->getID();
      unsigned int targetPinIndex = p->pinIndex();

      this->removeConnection(sourceBlockID,sourcePinIndex,targetBlockID,targetPinIndex);
    }
  }

  blockMap.erase(blockID);
  delete blockToBeRemoved;

  emit blockRemoved(blockID);
}
itemID script::getFreeID()
{
  //...maybe do this in a not so bruteforce way when i have time...no hurry!
  itemID newID = 0;
  while ( !isIDFree(newID) )
  {
    newID++;
  }
  return newID;
}
bool script::isIDFree(const itemID id)
{
  return blockMap.find(id) == blockMap.end();
}
void script::createBlock(const QString methodeName, const QPoint position, const itemID ID)
{
   unsigned int newID;

   if(ID >= 0)
   {
     if( isIDFree(ID) )
     {
       //ID is free to use
       newID = (unsigned int)ID;
     }
     else
     {
       throw blockIDNotFree_error(ID, __func__);
     }
   }
   else
   {
     newID = getFreeID();
   }

  callDefinition* blockDef = parentProject->getcallDefinition(methodeName);
  call* newBlock = new call(newID, blockDef);
  newBlock->setPos(position);
  blockMap.insert( std::make_pair(newID,newBlock) );

  //blockevent_moved(const itemID blockID, const QPoint newPositon, const QPoint movement);
  //blockevent_moved(const itemID blockID, const QPoint newPositon, const QPoint movement);

  connect(newBlock, SIGNAL(blockMoved      (const itemID, const QPoint, const QPoint)),
              this, SLOT  (blockevent_moved(const itemID, const QPoint, const QPoint)));

  emit blockCreated(newID);
}
void script::blockevent_moved(const itemID blockID, const QPoint newPositon, const QPoint movement)
{
  emit blockMoved(blockID,newPositon,movement);
}

}
