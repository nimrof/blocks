#include <stdexcept>
#include "calldefinition.h"
#include "exceptions.h"

#include "library.h"
#include <QString>

namespace blocks
{

callDefinition::callDefinition(library *parent)
{
  parentLibrary = parent;
}
void callDefinition::setLibrary(library* parent)
{
  parentLibrary = parent;
}
library* callDefinition::getLibrary()
{
  return parentLibrary;
}

void callDefinition::setName(QString newName)
{
  name = newName;
}
QString callDefinition::getName(void) const
{
  return name;
}
QString callDefinition::getFullName(void) const
{
  if(parentLibrary == NULL)
  {
    return QString("::%1").arg( getName() );
  }
  else
  {
    return QString("%1::%2").arg( parentLibrary->getName() ).arg( getName() );
  }
}
void callDefinition::addPin(const pinType pt, pinDefinition* newPin)
{
  switch(pt)
  {
  case input:
    pinIn.push_back(newPin);
    break;
  case output:
    pinOut.push_back(newPin);
    break;
  }
}
bool callDefinition::removePin(const pinType pt, itemID index)
{
  std::vector<pinDefinition*>* pPinList;

  switch(pt)
  {
  case input:
    pPinList = &pinIn;
    break;
  case output:
    pPinList = &pinOut;
    break;
  default:
    throw std::invalid_argument("pt can only be a enum of type pinType");
  }

  try
  {
    std::vector<pinDefinition*>::iterator it = pPinList->begin();
    it+index;
    if(it != pPinList->end())//TODO: test the bound checking
    {
      pPinList->erase(it);
      return true;
    }
    else
    {
      return false;
    }
  }
  catch (std::out_of_range& e)
  {
    return false;
  }
}
pinDefinition* callDefinition::getPin(const pinType pt,const itemID index) const
{
  const std::vector<pinDefinition*>* pPinList;

  switch(pt)
  {
  case input:
    pPinList = &pinIn;
    break;
  case output:
    pPinList = &pinOut;
    break;
  default:
    throw std::invalid_argument("pt can only be a enum of type pinType");
  }

  std::vector<pinDefinition*>::const_reference ref = pPinList->at(index);//might throw std::out_of_range
  return ref;
}
itemID callDefinition::getNumPinsOfType(const pinType pt) const
{
  switch(pt)
  {
  case input:
    return pinIn.size();
  case output:
    return pinOut.size();
  default:
    throw std::invalid_argument("pt can only be a enum of type pinType");
  }
}
void callDefinition::saveToXML(QDomElement &node, const int version) const
{
  if(!pinIn.empty() )
  {
    QDomElement inputNode = node.ownerDocument().createElement("input");
    node.appendChild(inputNode);

    std::vector<pinDefinition*>::const_iterator cIt;
    for ( cIt = pinIn.begin(); cIt != pinIn.end(); cIt++ )
    {
      (*cIt)->saveToXML(inputNode,version);
    }
  }

  if(!pinOut.empty() )
  {
    QDomElement outputNode = node.ownerDocument().createElement("output");
    node.appendChild(outputNode);

    std::vector<pinDefinition*>::const_iterator cIt;
    for ( cIt = pinOut.begin(); cIt != pinOut.end(); cIt++ )
    {
      (*cIt)->saveToXML(outputNode,version);
    }
  }
}
callDefinition* callDefinition::readFromXML(const QDomElement node, const int version)
{
  callDefinition* blockDef = new callDefinition(NULL);
  blockDef->setName( node.attribute("name") );

  QDomElement inputNode  = node.firstChildElement("input");
  QDomElement outputNode = node.firstChildElement("output");

  if(!inputNode.isNull())
  {
    QDomElement pin = inputNode.firstChildElement("pin");
    itemID pinIndex = 0;
    while (!pin.isNull())
    {
      pinDefinition* pinDef = pinDefinition::readFromXML(pin, version, pinIndex);
      blockDef->addPin(input,pinDef);
      pin = pin.nextSiblingElement("pin");
      pinIndex++;
    }
  }

  if(!outputNode.isNull())
  {
    QDomElement pin = outputNode.firstChildElement("pin");
    itemID pinIndex = 0;
    while (!pin.isNull())
    {
      pinDefinition* pinDef = pinDefinition::readFromXML(pin, version, pinIndex);
      blockDef->addPin(output,pinDef);
      pin = pin.nextSiblingElement("pin");
      pinIndex++;
    }
  }

  return blockDef;
}

}
