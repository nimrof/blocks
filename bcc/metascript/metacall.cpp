#include "metacall.h"
#include "calldefinition.h"
#include "pin.h"

#include <map>
#include <iostream>

metaCall::metaCall()
{
  type = _call;
}

metaCall::metaCall(const blocks::call &c, const std::map<outputVariableSource, blocks::itemID> &varSource2VarID)
{
  type = _call;
  functionName = c.getcallDefinition()->getFullName();
  blockID = c.getID();

  blocks::itemID numInput  = c.getNumPinsOfType(blocks::input);
  blocks::itemID numOutput = c.getNumPinsOfType(blocks::output);

  for (blocks::itemID i = 0; i < numInput; ++i)
  {
    const blocks::pin* p = c.getPinAt(i, blocks::input);

    if ( p->numConnections() != 1 )
    {
      std::cerr << "Input pin is not connected [Block=" << c.getID() << ",IPIN=" << i << "]" << std::endl;
      //TODO: Add fatal compiler error exception
    }
    else
    {
      const blocks::pin*sourcePin = p->getConnectionTarget(0);
      outputVariableSource sourceVariableInfo( sourcePin->getParentBlock()->getID(), sourcePin->pinIndex() );

      std::map<outputVariableSource, blocks::itemID>::const_iterator result;
      result = varSource2VarID.find(sourceVariableInfo);
      if( result == varSource2VarID.end() )
      {
        std::cerr << "internal error in file : " << __FILE__ << "at line: " << __LINE__ << std::endl;
        //TODO: Add fatal compiler error exception
      }
      inVariable.push_back(result->second);
    }
  }


  for (blocks::itemID i = 0; i < numOutput; ++i)
  {
    const blocks::pin* p = c.getPinAt(i, blocks::output);

    outputVariableSource sourceVariableInfo(c.getID(), p->pinIndex());//inside the loop to improve read quality


    std::map<outputVariableSource, blocks::itemID>::const_iterator result;
    result = varSource2VarID.find(sourceVariableInfo);
    if( result == varSource2VarID.end() )
    {
      std::cerr << "internal error in file : " << __FILE__ << "at line: " << __LINE__ << std::endl;
      //TODO: Add fatal compiler error exception
    }

    this->outVariable.push_back(result->second);
  }
}
