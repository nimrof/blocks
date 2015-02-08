#ifndef METASCRIPT_H
#define METASCRIPT_H

#include "blocks.h"
#include "blockvariable.h"

#include <map>
#include <vector>

#include "astElement.h"
#include "astFunctionCall.h"
#include "astBranch.h"

class metaWhile : public astElement
{
public:
  blocks::itemID         conditionVariable;
  std::vector<astElement*> lines;
};

class metaSwitch : public astElement
{
  //TODO
};

class metaScript
{
public:
  typedef std::vector<astElement*> branch;
  struct variableEntry
  {
    blocks::dataType          type;
    bool                      isConstant;
    blocks::blockDataVariable constantValue;
  };

  metaScript();
  bool makeFromScript(const blocks::script &s);
private:
  bool walkTree(const blocks::script &s);
  void walkBlock(const blocks::script &s, std::vector<bool> &doneID, const blocks::itemID blockID, astElement &branch);

  void registerVariables(const blocks::script &s);
  blocks::itemID getVariableIDfromBlockID(blocks::itemID constBlockID);

  bool blockInputVariablesReady(const std::vector<bool> doneIDs, const blocks::script &s, blocks::itemID blockID);
  std::vector<blocks::itemID> positionBasedSort(const std::vector<blocks::itemID> list, const blocks::script &s);
  astElement* allocateLineForBlock(const blocks::script &s, const blocks::itemID blockID);
  void mapVariableUsage();

  void printBranch(const int indent, const astElement &b);
  void mapVariableLifeInBranch(const blocks::itemID variableIndex, astElement** created, std::vector <astElement*> &read, astElement &b);

  std::vector<variableEntry>                     variables;
  std::map<outputVariableSource, blocks::itemID> varSource2VarID;

  astElement mainBranch;
//  std::vector<metaLine*> mainBranch;
};

#endif // METASCRIPT_H
