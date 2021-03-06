#include "config.h"

#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H

typedef unsigned char  BLUnsigned8;
typedef   signed char  BLSigned8;
typedef unsigned short BLUnsigned16;
typedef   signed short BLSigned16;
typedef unsigned int   BLUnsigned32;
typedef   signed int   BLSigned32;
typedef float          BLFloat32;
typedef float          BLFloat64;

typedef BLUnsigned8    BLChar;
typedef BLUnsigned8    BLBool;
typedef BLUnsigned8    BLResult;

#if BLOCKS_INTEGER_SIZE == 8
  typedef BLUnsigned8  BLUInt;
#elif BLOCKS_INTEGER_SIZE == 16
  typedef BLUnsigned16 BLUInt;
#elif BLOCKS_INTEGER_SIZE == 32
  typedef BLUnsigned32 BLUInt;
#endif

#if BLOCKS_VARIABLE_INDEX_SIZE == 8
  typedef BLUnsigned8  BLNumVariable;
#elif BLOCKS_VARIABLE_INDEX_SIZE == 16
  typedef BLUnsigned16 BLNumVariable;
#elif BLOCKS_VARIABLE_INDEX_SIZE == 32
  typedef BLUnsigned32 BLNumVariable;
#endif

#if BLOCKS_HASH_SIZE == 8
  typedef BLUnsigned8  BLHash;
#elif BLOCKS_HASH_SIZE == 16
  typedef BLUnsigned16 BLHash;
#elif BLOCKS_HASH_SIZE == 32
  typedef BLUnsigned32 BLHash;
#endif

#define bl_OK    0
#define bl_ERROR 1

#endif
