/*!
 * <File comment goes here!!>
 * 
 * Copyright (c) 2010 by Lars Elgtvedt Susaas
 */

#pragma once
#include <string>
#include <map>

#include "BlocksType.h"
#include "blCall.h"

class blocksFunctionList
{
  public:
    BLResult registerFunction (const bl_function function, const std::string Name);
    BLResult findFunction     (const BLHash nameHash, bl_function* pFunction) const;
  private:
    BLHash jenkins_one_at_a_time_hash(const std::string) const;
    std::map<BLHash,bl_function> functionDictinary;
};
