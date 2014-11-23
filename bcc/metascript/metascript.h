#ifndef METASCRIPT_H
#define METASCRIPT_H

#include "blocks.h"
#include "blockvariable.h"

#include <map>
#include <vector>

#include "metaline.h"
#include "metacall.h"
#include "metabranch.h"

class metaWhile : public metaLine
{
public:
  blocks::itemID         conditionVariable;
  std::vector<metaLine*> lines;
};

class metaSwitch : public metaLine
{
  //TODO
};

class metaScript
{
public:
  typedef std::vector<metaLine*> branch;
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
  void walkBlock(const blocks::script &s, std::vector<bool> &doneID, const blocks::itemID blockID, metaLine &branch);

  void registerVariables(const blocks::script &s);
  blocks::itemID getVariableIDfromBlockID(blocks::itemID constBlockID);

  bool blockInputVariablesReady(const std::vector<bool> doneIDs, const blocks::script &s, blocks::itemID blockID);
  std::vector<blocks::itemID> positionBasedSort(const std::vector<blocks::itemID> list, const blocks::script &s);
  metaLine* allocateLineForBlock(const blocks::script &s, const blocks::itemID blockID);
  void mapVariableUsage();

  void printBranch(const int indent, const metaLine &b);
  void mapVariableLifeInBranch(const blocks::itemID variableIndex, metaLine** created, std::vector <metaLine*> &read, metaLine &b);

  std::vector<variableEntry>                     variables;
  std::map<outputVariableSource, blocks::itemID> varSource2VarID;

  metaLine mainBranch;
//  std::vector<metaLine*> mainBranch;
};

#endif // METASCRIPT_H
