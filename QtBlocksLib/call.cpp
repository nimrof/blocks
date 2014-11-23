#include <stdexcept>

#include "call.h"
#include "calldefinition.h"
#include "pin.h"

namespace blocks
{

call::call (const itemID ID, callDefinition* callDef) : block(ID)
{
  bType = block::callBlock;
  definition = callDef;

  std::vector<pin>::iterator it;

  for (itemID i = 0; i < definition->getNumPinsOfType(input); i++)
  {
    inputPins.push_back(  new pin(definition->getPin(input,i), this,  input) );
  }
  for (itemID i = 0; i < definition->getNumPinsOfType(output); i++)
  {
    outputPins.push_back( new pin(definition->getPin(output,i),this, output) );
  }
}
callDefinition* call::getcallDefinition() const
{
  return definition;
}

}
