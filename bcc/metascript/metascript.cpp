#include "metascript.h"

#include "script.h"
#include "block.h"
#include "call.h"
#include "calldefinition.h"
#include "pin.h"
#include "constant.h"
#include "blockvariable.h"

#include <map>
#include <utility>
#include <iostream>

#include <string>

metaScript::metaScript()
{
}
bool metaScript::makeFromScript(const blocks::script &s)
{
  registerVariables(s);
  walkTree(s);
  printBranch(0,mainBranch);
  mapVariableUsage();
  return true;
}
void metaScript::registerVariables(const blocks::script &s)
{
  blocks::itemID numBlocks = s.getNumBlocks();

  for(blocks::itemID i = 0; i < numBlocks; i++)
  {
    const blocks::block* block = s.getBlock(i);
    unsigned int numOutputPin = block->getNumPinsOfType(blocks::output);

    for(unsigned int p = 0; p < numOutputPin; p++)
    {
      const blocks::pin* outPin = block->getPinAt(p,blocks::output);

      variableEntry newConst;
      newConst.type = outPin->datatype();

      newConst.isConstant = block->type() == blocks::block::constantBlock;
      newConst.constantValue.i32 = 0;//for debugging
      if(newConst.isConstant)
      {
        const blocks::constant* blockConst = static_cast<const blocks::constant*>(block);
        newConst.constantValue = blockConst->constObj().getVariable();
      }
      variables.push_back(newConst);
      varSource2VarID.insert( std::pair<outputVariableSource, blocks::itemID>( outputVariableSource(i,p),variables.size() -1) );
    }
  }
}
bool metaScript::walkTree(const blocks::script &s)
{
  std::vector <bool> doneID;
  std::vector <blocks::itemID> list;
  std::vector <blocks::itemID> slist;//sorted list

  blocks::itemID numBlocks = s.getNumBlocks();
  doneID.resize(numBlocks,false);

  for(blocks::itemID i = 0; i < numBlocks; i++)
  {
    list.push_back(i);
  }

  slist = positionBasedSort(list,s);

  blocks::itemID calledBlock = 0;

  for(blocks::itemID i = 0; i < numBlocks; i++)
  {
    if(s.getBlock(slist[i])->type() == blocks::block::constantBlock)
    {
      doneID.at( slist[i] ) = true;
    }
  }

  while(calledBlock != numBlocks)
  {
    for(blocks::itemID i = 0; i < numBlocks; i++)
    {
      if(doneID.at(slist[i]))
      {
        continue;
      }
      if( blockInputVariablesReady( doneID,s,slist[i] ) )
      {
        walkBlock(s, doneID, slist[i], mainBranch);
        break;
      }
    }
    calledBlock = std::count (doneID.begin(), doneID.end(), true);
  }
  return true;
}
void metaScript::walkBlock(const blocks::script &s, std::vector<bool> &doneID, const blocks::itemID blockID, metaLine &branch)
{
  doneID.at(blockID) = true;
  branch.children.push_back( allocateLineForBlock(s,blockID) );

  const blocks::block* block = s.getBlock(blockID);

  blocks::itemID outputPins = block->getNumPinsOfType(blocks::output);

  for(blocks::itemID i = 0; i < outputPins; i++)
  {
    const blocks::pin* pin = block->getPinAt(i,blocks::output);
    size_t connections = pin->numConnections();

    std::vector<blocks::itemID> connectedBlocks;

    for(size_t c = 0; c < connections; c++)
    {
      blocks::itemID connectedBlock = pin->getConnectionTarget(c)->getParentBlock()->getID();
      connectedBlocks.push_back(connectedBlock);
    }
    connectedBlocks = positionBasedSort(connectedBlocks,s);

    for(size_t c = 0; c < connections; c++)
    {
      blocks::itemID targetedBlockID = connectedBlocks.at(c);

      if( (doneID.at(connectedBlocks.at(c)) == false) && blockInputVariablesReady( doneID,s,targetedBlockID ) )
      {
        walkBlock(s,doneID,connectedBlocks.at(c),branch);
      }
    }
  }
}

bool metaScript::blockInputVariablesReady(const std::vector<bool> doneIDs, const blocks::script &s, const blocks::itemID blockID)
{
  const blocks::block* block = s.getBlock(blockID);
  blocks::itemID NumPins = block->getNumPinsOfType(blocks::input);

  for(blocks::itemID p = 0; p < NumPins; p++)
  {
    const blocks::pin* targetPin = block->getPinAt(p,blocks::input);
    if (targetPin->numConnections() != 1)
    {
      std::cerr << "internal error in file : " << __FILE__ << "at line: " << __LINE__ << std::endl;
    }
    else
    {
      const blocks::pin* sourcePin = targetPin->getConnectionTarget(0);
      blocks::itemID sourceBlockID = sourcePin->getParentBlock()->getID();

      if(!doneIDs.at(sourceBlockID))
      {
        return false;
      }
    }
  }
  return true;
}
std::vector<blocks::itemID> metaScript::positionBasedSort(const std::vector<blocks::itemID> list, const blocks::script &s)
{
  std::vector<blocks::itemID> sortedList;
  //'quick' and dirty sort

  for (std::vector<blocks::itemID>::const_iterator it = list.begin() ; it != list.end(); ++it)
  {
    const blocks::block* unsortedBlock = s.getBlock(*it);

    bool isHigher = false;//should be lower on the sorted list.. as in has higher x pos (and posibly y)

    if(sortedList.empty())
    {
      sortedList.push_back(*it);
    }
    else
    {
      std::vector<blocks::itemID>::iterator sit = sortedList.begin();
      const blocks::block* sortedBlock = s.getBlock(*sit);

      while( sit != sortedList.end() && !isHigher )
      {
        sortedBlock = s.getBlock(*sit);
        if( unsortedBlock->pos().x() == sortedBlock->pos().x() )
        {
          isHigher = unsortedBlock->pos().y() < sortedBlock->pos().y();
        }
        else
        {
          isHigher = unsortedBlock->pos().x() < sortedBlock->pos().x();
        }

        if(isHigher)
        {
          sortedList.insert(sit,*it);
          break;
        }
        else
        {
          sit++;
        }
      }

      if(sit == sortedList.end())
      {
        sortedList.push_back(*it);
      }
    }
  }
  return sortedList;
}
metaLine* metaScript::allocateLineForBlock(const blocks::script &s, const blocks::itemID blockID)
{
  metaLine* resultLine = 0;
  blocks::block const* b = s.getBlock(blockID);

  switch( b->type() )
  {
    case blocks::block::callBlock:
      {
        const blocks::call* callBlock = static_cast<const blocks::call*>(b);
        const blocks::callDefinition* definition = callBlock->getcallDefinition();

        blocks::itemID NumPins = definition->getNumPinsOfType(blocks::output);

        metaCall* callLine = new metaCall(*callBlock, varSource2VarID);

        bool branches = false;
        for(blocks::itemID p = 0; p < NumPins; p++)
        {
          //TODO: compact code, but not the most efficient (replace with c11 std::any_of
          branches = (definition->getPin(blocks::output, p)->getDataType() == blocks::RUN) || branches;
        }

        if( branches )
        {
          //TODO:: code metascript callblocks with branches
        }
        else
        {
          resultLine = callLine;
        }
      }
      break;
    case blocks::block::constantBlock:
      //nothing to do...
      break;
  }
  return resultLine;
}
void metaScript::printBranch(const int indent, const metaLine &b)
{
  //metaLine->curLine
  //  while()

  for (std::vector<metaLine*>::const_iterator it = b.children.begin() ; it != b.children.end(); ++it)
  {
    std::cout << std::string(indent, '-');

    metaLine* l = (*it);
    switch(l->type)
    {
      case metaLine::_call:
        {
          metaCall* c = static_cast<metaCall*>(l);
          std::cout << (char*)c->functionName.toLocal8Bit().data();

          std::cout << "  \t";
          if( !c->inVariable.empty() )
          {
            std::cout << "<<";
            for (std::vector<blocks::itemID>::const_iterator v = c->inVariable.begin() ; v != c->inVariable.end(); ++v)
            {
              std::cout << (blocks::itemID)*v;
              if( v+1 != c->inVariable.end() )
              {
                std::cout << ",";
              }
            }
          }
          std::cout << "  \t";
          if( !c->outVariable.empty() )
          {

            std::cout << ">>";
            for (std::vector<blocks::itemID>::const_iterator v = c->outVariable.begin() ; v != c->outVariable.end(); ++v)
            {
              std::cout << (blocks::itemID)*v;
              if( v+1 != c->outVariable.end() )
              {
                std::cout << ",";
              }
            }
          }
        }
        break;
      case metaLine::_branching:
        break;
      case metaLine::_while:
        break;
      case metaLine::_for:
        break;
      case metaLine::_switch:
        break;
    }

    std::cout << std::endl;
    printBranch(0,**it);//TODO: do indent
  }
}
void metaScript::mapVariableUsage()
{
  std::vector<metaLine*>               variableCreated;
  std::vector<std::vector<metaLine*> > variableRead;

  size_t numVariables = variables.size();
  variableCreated.resize( numVariables );
  variableRead.resize(    numVariables );

  for (size_t i = 0; i < numVariables; i++)//TODO: this can be multithreaded
  {
    if(variables[i].isConstant == false)
    {
      mapVariableLifeInBranch(i, &variableCreated[i], variableRead[i], mainBranch);
    }
  }

  for (size_t i = 0; i < numVariables; i++)
  {
    if(variables[i].isConstant == false)
    {

    }
  }
}
void metaScript::mapVariableLifeInBranch(const blocks::itemID variableIndex, metaLine** created, std::vector <metaLine*> &read, metaLine &b)
{/*
  for (std::vector<metaLine*>::const_iterator it = b.begin() ; it != b.end(); ++it)
  {
    metaLine* l = (*it);
    switch(l->type)
    {
      case metaLine::_call:
        {
          metaCall* c = static_cast<metaCall*>(l);
          for (std::vector<blocks::itemID>::const_iterator v = c->inVariable.begin() ; v != c->inVariable.end(); ++v)
          {
            if( (blocks::itemID)*v == variableIndex )
            {
              read.push_back(l);
            }
          }
          for (std::vector<blocks::itemID>::const_iterator v = c->outVariable.begin() ; v != c->outVariable.end(); ++v)
          {
            if( (blocks::itemID)*v == variableIndex )
            {
              *created = l;
            }
          }
        }
        break;
      case metaLine::_branching:
        break;
      case metaLine::_while:
        break;
      case metaLine::_for:
        break;
      case metaLine::_switch:
        break;
    }
  }*/
}
