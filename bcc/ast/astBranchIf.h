#ifndef METAIF_H
#define METAIF_H

#include "astElement.h"

#include <map>

class astIf : public astElement
{
public:
  astIf();
  //metaCall branchingBlock;
  std::map<blocks::itemID, std::vector<astElement*> > branches;//branchPin and the branch itself
};

#endif // METAIF_H
