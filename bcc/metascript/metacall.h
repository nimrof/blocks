#ifndef METACALL_H
#define METACALL_H

#include "metaline.h"
#include "blocks.h"
#include "call.h"

#include <vector>
#include <map>
#include <QString>

class metaCall : public metaLine
{
public:
  metaCall();
  metaCall(const blocks::call &c, const std::map<outputVariableSource, blocks::itemID> &varSource2VarID);
  QString                 functionName;
  std::vector<blocks::itemID> inVariable;
  std::vector<blocks::itemID> outVariable;
};

#endif // METACALL_H
