#include <stdexcept>

#include "block.h"
#include "pin.h"

namespace blocks
{

block::block(const itemID ID)
{
  this->ID = ID;
}
unsigned int block::getNumPinsOfType(const pinType pt) const
{
  switch(pt)
  {
    case input:
      return inputPins.size();
    case output:
      return outputPins.size();
    default:
      throw std::invalid_argument("pt can only be a enum of type pinType");
  }
}
pin* block::getPinAt(const itemID index, const pinType type)
{
  std::vector<pin*>* pPinList;

  switch(type)
  {
    case input:
      pPinList = &inputPins;
      break;
    case output:
      pPinList = &outputPins;
      break;
    default:
      throw std::invalid_argument("pt can only be a enum of type pinType");
  }

  std::vector<pin*>::reference ref = pPinList->at(index);//might throw std::out_of_range
  return ref;
}

const pin* block::getPinAt(const itemID index, const pinType type) const
{
  const std::vector<pin*>* pPinList;

  switch(type)
  {
    case input:
      pPinList = &inputPins;
      break;
    case output:
      pPinList = &outputPins;
      break;
    default:
      throw std::invalid_argument("pt can only be a enum of type pinType");
  }

  std::vector<pin*>::const_reference ref = pPinList->at(index);//might throw std::out_of_range
  return ref;
}

size_t block::getPinIndex(const pin *p,const pinType type)
{
  std::vector<pin*>* pPinList;

  switch(type)
  {
  case input:
    pPinList = &inputPins;
    break;
  case output:
    pPinList = &outputPins;
    break;
  default:
    throw std::invalid_argument("pt can only be a enum of type pinType");
  }

  std::vector<pin*>::iterator it;
  it = std::find(pPinList->begin(), pPinList->end(), p);

  if ( it != pPinList->end() )
  {
    return std::distance(pPinList->begin(), it);
  }
  else
  {
    return 99;
  }
}
void block::setPos(QPoint newPosition)
{
  QPoint movement = newPosition - position;
  position = newPosition;

  emit blockMoved(getID(), newPosition, movement);
}
QPoint block::pos() const
{
  return position;
}
block::Type block::type() const
{
  return bType;
}
itemID block::getID() const
{
  return ID;
}



}
