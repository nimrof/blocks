#ifndef METABRANCH_H
#define METABRANCH_H

#include "metaline.h"

#include <map>

class metaBranch : public metaLine
{
public:
  metaBranch();
  metaLine branchingBlock;
  std::map<blocks::itemID, std::vector<metaLine*> > branches;//branchPin and the branch itself
};


#endif // METABRANCH_H
