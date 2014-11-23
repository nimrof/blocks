#ifndef METALINE_H
#define METALINE_H

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

class metaLine
{
public:
  metaLine();
  enum _type
  {
    _noop,//no-op.....does nothing
    _call,
    _if,
    _while,
    _for,
    _for_each,
    _switch,
    _branching
  };
  _type type;

  blocks::itemID blockID;
  std::vector <blocks::itemID> currentVariableUsage;//variable usage at this point in the script
  std::vector <metaLine*> parents;//can be multiple when branches meets
  std::vector <metaLine*> children;//can be multiple when branches......are branching?
};

#endif // METALINE_H
