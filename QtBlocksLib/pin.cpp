#include <algorithm>

#include "pin.h"
#include "call.h"

namespace blocks
{

pin::pin(pinDefinition* pinDef, block* parent, const pinType pint)
{
  definition   = pinDef;
  this->parent = parent;
  pt           = pint;
  index        = pinDef->getIndex();
}
block* pin::getParentBlock() const
{
  return parent;
}
dataType pin::datatype() const
{
  return definition->getDataType();
}
pinType pin::pintype() const
{
  return pt;
}
bool pin::addConnectionTo(pin* targetPin)
{
/*
  if ( pt == input  )
  {
    throw "internal error: you can not add a connection from a input pin, must be of type output";
  }
*/
  if ( targetPin->datatype() != datatype() )
  {
    throw "pin from block %1 can not be connected to block %2 as they have different datatypes";
  }
/*
  if ( targetPin->pintype() == output )
  {
    throw "can not connect output pin to output pin";
  }*/

  //Is it already connected?
  if ( std::find(targetPins.begin(), targetPins.end(), targetPin) != targetPins.end() )
  {
    //already connected
    return false;
  }
  else
  {
    targetPins.push_back(targetPin);
    return true;
  }
}
bool pin::removeConnectionTo(pin* targetPin)
{
  std::vector <pin*>::iterator it;

  it = std::find(targetPins.begin(), targetPins.end(), targetPin);

  if ( it != targetPins.end() )
  {
    targetPins.erase(it);
    return true;
  }
  else
  {
    return false;
  }
}
bool pin::isConnected() const
{
  return !targetPins.empty();
}
size_t pin::numConnections() const
{
  return targetPins.size();
}
pin* pin::getConnectionTarget(size_t i)
{
  return targetPins.at(i);
}
const pin* pin::getConnectionTarget(size_t i) const
{
  return targetPins.at(i);
}
itemID pin::pinIndex() const
{
  return index;
}

}
