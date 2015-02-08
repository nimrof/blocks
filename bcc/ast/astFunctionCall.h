#ifndef ASTFUNCTIONCALL_H
#define ASTFUNCTIONCALL_H

#include "astElement.h"
#include "blocks.h"
#include "call.h"

#include <vector>
#include <map>
#include <QString>

class astFunctionCall : public astElement
{
public:
  astFunctionCall();
  astFunctionCall(const blocks::call &c, const std::map<outputVariableSource, blocks::itemID> &varSource2VarID);
  QString                 functionName;
  std::vector<blocks::itemID> inVariable;
  std::vector<blocks::itemID> outVariable;
};

#endif // ASTFUNCTIONCALL_H
