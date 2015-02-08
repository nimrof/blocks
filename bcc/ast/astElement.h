#ifndef ASTELEMENT_H
#define ASTELEMENT_H

#include "blocks.h"
#include <vector>

struct outputVariableSource
{
  outputVariableSource(const blocks::itemID blockID,const blocks::itemID outputPinID)
  {
    this->blockID     = blockID;
    this->outputPinID = outputPinID;
  }
  blocks::itemID blockID;
  blocks::itemID outputPinID;

  bool operator<( const outputVariableSource & ov ) const
  {
    if(ov.blockID == blockID)
    {
      return outputPinID < ov.outputPinID;
    }
    else
    {
      return blockID < ov.blockID;
    }
  }
};

class astElement
{
public:
  astElement();
  enum _type
  {
    _noop,//no-op.....does nothing
    _functioncall,
    _branch,
  };
  _type type;

  blocks::itemID blockID;
  std::vector <blocks::itemID> currentVariableUsage;//variable usage at this point in the script
  std::vector <astElement*> parents;//can be multiple when branches meets
  std::vector <astElement*> children;//can be multiple when branches......are branching?
};

#endif // ASTELEMENT_H
