#include "blHash.h"

#if BLOCKS_HASH_SIZE == 32 || defined(ADV_BLOCKS_VM)
/*!
 * \brief
 * jenkins one at a time hash
 *
 * \param key
 * Pointer to the data area to make a hash from.
 *
 * \param key_len
 * Length of the data area to make the hash from.
 *
 * \returns
 * Hash value if the data
 *
 * \remark
 * http://en.wikipedia.org/wiki/Jenkins_hash_function
 *
 * \see
 *
 */
BLUnsigned32 jenkins_one_at_a_time_hash(const char* key, const BLUInt key_len)
{
  BLUnsigned32 hash = 0;
  BLUInt i;
 
  for (i = 0; i < key_len; i++)
  {
    hash += key[i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }
  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
  return hash;
}
#elif BLOCKS_HASH_SIZE == 16 || defined(ADV_BLOCKS_VM)
/*!
 * \brief
 * Dan Bernstein hash
 *
 * \param key
 * Pointer to the data area to make a hash from.
 *
 * \param key_len
 * Length of the data area to make the hash from.
 *
 * \returns
 * Hash value if the data
 *
 * \remark
 *
 * \see
 *
 */
BLUnsigned16 dan_bernstein_hash(const char* key, const BLUInt key_len)
{
  BLUInt  i;
  BLUnsigned16 hash = 5381;//not sure if this start value is common

  for (i = 0; i < key_len; i++)
  {
    hash = hash * 33 ^ key[i];
  }
  return hash;
}
#elif BLOCKS_HASH_SIZE == 8 || defined(ADV_BLOCKS_VM)
/*!
 * \brief
 * Pearson hashing
 *
 * \param key
 * Pointer to the data area to make a hash from.
 *
 * \param key_len
 * Length of the data area to make the hash from.
 *
 * \returns
 * Hash value if the data
 *
 * \remark
 * http://en.wikipedia.org/wiki/Pearson_hashing
 *
 * \see
 *
 */

//const char T[0xFF] = {0};//TODO... random

BLUnsigned8 pearson_hashing(const char* key, const BLUInt key_len)
{
  BLUInt  i;
  unsigned char h = 0;
  unsigned char index;

  for (i = 0; i < key_len; i++)
  {
    index = h ^ key[i];
//    h = T[index];//TODO... see T
    h = index;
  }
  return h;
}
#endif
