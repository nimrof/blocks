/*!
 * <File comment goes here!!>
 * 
 * Copyright (c) 2010 by Lars Elgtvedt Susaas
 */

#pragma once
#include "BlocksType.h"

#if BLOCKS_HASH_SIZE == 32 || defined(ADV_BLOCKS_VM)
  BLUnsigned32 jenkins_one_at_a_time_hash(const char* key, BLUInt key_len);
  #if !defined(ADV_BLOCKS_VM)
    #define blHash jenkins_one_at_a_time_hash
  #else
    #define blHash32
  #endif
#endif

#if BLOCKS_HASH_SIZE == 16 || defined(ADV_BLOCKS_VM)
  BLUnsigned16 dan_bernstein_hash(const char* key, const BLUInt key_len);
  #if !defined(ADV_BLOCKS_VM)
    #define blHash dan_bernstein_hash
  #else
    #define blHash16
  #endif
#endif

#if BLOCKS_HASH_SIZE == 8 || defined(ADV_BLOCKS_VM)
  BLUnsigned8  pearson_hashing(const char* key, const BLUInt key_len);
  #if !defined(ADV_BLOCKS_VM)
    #define blHash pearson_hashing
  #else
    #define blHash8
  #endif
#endif