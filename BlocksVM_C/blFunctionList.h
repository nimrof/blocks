/*!
 * <File comment goes here!!>
 * 
 * Copyright (c) 2010 by Lars Elgtvedt Susaas
 */

#ifndef BLFUNCTIONLIST_H
#define BLFUNCTIONLIST_H

#include "BlocksType.h"
#include "blVM.h"

BLResult    blRegisterFunction (HBLOCKSVM vm, bl_function function, char* Name);
BLResult    blFindFunction     (HBLOCKSVM v, BLHash nameHash, bl_function* pFunction);

#endif
