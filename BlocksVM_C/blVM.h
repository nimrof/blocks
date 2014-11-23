/*!
 * <File comment goes here!!>
 * 
 * Copyright (c) 2010 by Lars Elgtvedt Susaas
 */

#pragma once
#include "BlocksType.h"

#define DefaultMethodeListSize 256

typedef struct sblVM*          HBLOCKSVM;
typedef struct sblVM            BLOCKSVM;
typedef struct blCallStruct* HBLOCKSCALL;

typedef BLResult (*bl_function)(HBLOCKSCALL CallData);

struct blFunctionListElement
{
  BLHash      hash;
  bl_function function;
};

struct blCallStruct
{
  BLNumVariable  maxIOVar;//for safety check
  BLNumVariable  numInput;
  BLNumVariable  numOutput;
  BLNumVariable  inputIndex;
  BLNumVariable  outputIndex;
  BLHash         functionHash;
  BLNumVariable* inputs;
  BLNumVariable* outputs;
};

struct sblVM
{
  char*                         buffer;
  BLUnsigned16                  bufferSize;
  BLUnsigned8                   hasLoadedScript;
  BLHash                        numFunctions;//init this to BLHash-1
//  struct blCallStruct           CallData;
  struct blFunctionListElement* functionList;//Put this LAST!!!!!!!
};

