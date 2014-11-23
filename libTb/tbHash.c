/*!
 * Source of the jenkins_one_at_a_time_hash function
 * 
 * found in wikipedia
 */

#include "tbHash.h"

/*!
 * \brief
 * Makes a Hash value.
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
unsigned int jenkins_one_at_a_time_hash(unsigned char* key, unsigned int key_len)
{
  unsigned int hash = 0;
  unsigned int i;
 
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

#ifdef TODO
unsigned char Pearson_hashing(unsigned char* key, unsigned int key_len)
{
  unsigned int  i;
  unsigned char h = 0;

  for (i = 0; i < key_len; i++)
  {
    index := h ^ key[i - 1]
    h := T[index mod t]
  }
  return h
}
#endif