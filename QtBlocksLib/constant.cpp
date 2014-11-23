#include "constant.h"
#include "pindefinition.h"
#include "pin.h"

namespace blocks
{

constant::constant(const itemID ID) : block(ID)
{
  bType = constantBlock;
}
constant::constant(const itemID ID, const QString type, const QString value) : block(ID)
{
  bType = constantBlock;
  constantValue = blockVariable(type,value);
  pinDefinition* pinDef = new pinDefinition("",constantValue.getDataType(),0);
  outputPins.push_back(new pin(pinDef, this,output));
}
constant::constant(const itemID ID, const blockVariable& constantValue) : block(ID)
{
  bType = constantBlock;
  this->constantValue = constantValue;
}
const blockVariable &constant::constObj(void) const
{
  return constantValue;
}

blockVariable& constant::Obj(void)
{
  return constantValue;
}

}
