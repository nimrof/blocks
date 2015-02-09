#ifndef METAIF_H
#define METAIF_H

#include "astElement.h"

#include <map>

class metaIf : public metaLine
{
public:
  metaIf();
  //metaCall branchingBlock;
  std::map<blocks::itemID, std::vector<metaLine*> > branches;//branchPin and the branch itself
};

#endif // METAIF_H
