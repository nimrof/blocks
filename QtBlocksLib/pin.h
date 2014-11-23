#ifndef PIN_H
#define PIN_H

#include <vector>

#include <QDomElement>

#include "blocks.h"
#include "pindefinition.h"

namespace blocks
{

class pin
{
public:
  pin                           (pinDefinition* pinDef, block* parent, const pinType pint);
  block*     getParentBlock     ()                                                          const;
  dataType   datatype           ()                                                          const;
  pinType    pintype            ()                                                          const;
  bool       addConnectionTo    (pin* targetPin);
  bool       removeConnectionTo (pin* targetPin);
  bool       isConnected        ()                                                          const;
  size_t     numConnections     ()                                                          const;
  pin*       getConnectionTarget(size_t i);
  const pin* getConnectionTarget(size_t i)                                                  const;
  itemID     pinIndex           ()                                                          const;
private:
  pinDefinition*     definition;
  block*             parent;
  std::vector <pin*> targetPins;
  pinType            pt;
  itemID             index;
};

}

#endif // PIN_H
