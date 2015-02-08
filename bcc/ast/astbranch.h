#ifndef ASTBRANCH_H
#define ASTBRANCH_H

#include "astElement.h"

#include <map>

class astBranch : public astElement
{
public:
  astBranch();
  enum _type
  {
    _if,
    _while,
    _for,
    _for_each,
    _switch,
    _branching,
  };
  _type type;

  astElement condition;
  std::map<blocks::itemID, std::vector<astElement*> > body;
};

#endif // ASTBRANCH_H
