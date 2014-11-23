/*!
 * Source for handeling methode registering and seaching
 * 
 * Copyright (c) 2010 by Lars Elgtvedt Susaas
 */

#include "blFunctionList.h"
#include "blVM.h"
#include <string.h>

/*!
 * \brief
 * Searches the VM methode list for methode that matches the hash.
 *
 * \param pVM
 * The virtual machine to search in.
 *
 * \param MethodenameHash
 * The hash value of the methode name to search for.
 *
 * \returns
 * pointer to function or 0 if not found
 *
 * \see
 * tbRegisterFunction
 */
BLResult blocksFunctionList::findFunction(const BLHash nameHash, bl_function* pFunction) const
{
  std::map<BLHash, bl_function>::const_iterator cit;

  cit = functionDictinary.find(nameHash);

  if(cit == functionDictinary.end() )
  {
    *pFunction = *cit->second;
    return bl_OK;
  }
  else
  {
    *pFunction = 0;//for safety
    return bl_ERROR;
  }
}
/*!
 * \brief
 * Adds a methode to the VM internal methode list.
 *
 * \param pVM
 * The virtual machine to register the methode in.
 *
 * \param Methode
 * The hash value of the methode name to search for.
 *
 * \param Name
 * The name of the function to register.
 *
 * \returns
 * TB_ERROR on error else TB_OK
 *
 * \see
 * tbFindMethode
 */
BLResult blocksFunctionList::registerFunction(const bl_function function, const std::string name)
{
  BLHash functionNameHash = jenkins_one_at_a_time_hash(name);

  std::pair< std::map<BLHash,bl_function>::iterator,bool > ret;

  ret = functionDictinary.insert( std::pair<BLHash,bl_function>(functionNameHash,function) );

  if(ret.second == false)
  {
    //other element exists already
    return bl_ERROR;
  }
  else
  {
    return bl_OK;
  }

}
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
BLUnsigned32 blocksFunctionList::jenkins_one_at_a_time_hash(const std::string name) const
{
  BLUnsigned32 hash = 0;
  size_t strLen = name.size();
  BLUInt i;

  for (i = 0; i < strLen; i++)
  {
    hash += name[i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }
  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
  return hash;
}