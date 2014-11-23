/*!
 * Source for handeling methode registering and seaching
 * 
 * Copyright (c) 2010 by Lars Elgtvedt Susaas
 */

#include "tbFunctionList.h"
#include "tbHash.h"
#include "tbVM.h"
#include <string.h>

#include <stdlib.h>
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
tb_method tbFindMethode(struct tbVM* pVM, unsigned int MethodenameHash)
{
  struct tb_MethodeListElement* LocatedEntry;
	
  LocatedEntry = (struct tb_MethodeListElement*)bsearch(&MethodenameHash,pVM->Methodes.MethodeList,pVM->Methodes.TopIndex,sizeof(pVM->Methodes.MethodeList[0]),tbMethodeKeyElementCompare);
	
  if(LocatedEntry)
  {
    return LocatedEntry->Methode;
  }
  else
  {
    return NULL;
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
int tbRegisterFunction(struct tbVM* pVM, tb_method Methode, char* Name)
{
  struct tb_MethodeListElement NewEntry;
  if(pVM->Methodes.ListSize < pVM->Methodes.TopIndex)
  {
    if( tbReallocMethodeList(pVM) == TB_ERROR)
    {
      return TB_ERROR;
    }
  }
  NewEntry.Hash    = jenkins_one_at_a_time_hash((unsigned char*)Name,strlen(Name));
  NewEntry.Methode = Methode;

  pVM->Methodes.MethodeList[pVM->Methodes.TopIndex] = NewEntry;
  pVM->Methodes.TopIndex++;

  qsort(pVM->Methodes.MethodeList,pVM->Methodes.TopIndex,sizeof(NewEntry), tbMethodeElementCompare);

  return TB_OK;
}
/*!
 * \brief
 * Reallocate the VM methode list and double the size of it.
 *
 * \param pVM
 * The virtual machine to realloc the methode list in.
 *
 * \returns
 * TB_ERROR on memory allocation error else TB_OK
 *
 * \remarks
 * Internal methode and should not be user directly.
 *
 * \see
 * tbRegisterFunction
 */
int tbReallocMethodeList(struct tbVM* pVM)
{
  struct tb_MethodeListElement* NewMethodeList;

  NewMethodeList = realloc(pVM->Methodes.MethodeList, (pVM->Methodes.ListSize * 2) * sizeof(pVM->Methodes.MethodeList) );
  if(NewMethodeList != NULL)
  {
    pVM->Methodes.MethodeList = NewMethodeList;
    return TB_OK;
  }
  else
  {
   return TB_ERROR;
  }
}
/*!
 * \brief
 * Compares two tb_MethodeListElement's hash value and returns the result.
 *
 * \param elem1
 * pointer to a MethodeListElement to compare with elem2.
 *
 * \param elem2
 * pointer to a MethodeListElement to compare with elem1.
 *
 * \returns
 * see full discription
 *
 * \remarks
 * Internal methode and should not be user directly.
 *
 * The function will return the following values
 * Compare function return value Description
 * < 0 elem1 hash less than elem2
 *   0 elem1 hash equivalent to elem2
 * > 0 elem1 hash greater than elem2
 *
 * \see
 * tbRegisterFunction tbMethodeKeyElementCompare
 */
int tbMethodeElementCompare( const void* elem1, const void* elem2 )
{
  const struct tb_MethodeListElement* arg1 = (const struct tb_MethodeListElement*) elem1;
  const struct tb_MethodeListElement* arg2 = (const struct tb_MethodeListElement*) elem2;

  if( arg1->Hash < arg2->Hash )
  {
    return -1;
  }
  else if( arg1->Hash > arg2->Hash )
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
/*!
 * \brief
 * Compares a key (hash value) with a tb_MethodeListElement's hash value and returns the result.
 *
 * \param elem1
 * Pointer to a hash value.
 *
 * \param elem2
 * pointer to a MethodeListElement to compare with elem1.
 *
 * \returns
 * see full discription
 *
 * \remarks
 * Internal methode and should not be user directly.
 *
 * The function will return the following values
 * Compare function return value Description
 * < 0 elem1 hash less than elem2
 *   0 elem1 hash equivalent to elem2
 * > 0 elem1 hash greater than elem2
 *
 * \see
 * tbFindMethode tbMethodeKeyElementCompare
 */
int tbMethodeKeyElementCompare( const void* elem1, const void* elem2 )
{
  const unsigned int* arg1 = (const unsigned int*) elem1;
  const struct tb_MethodeListElement* arg2 = (const struct tb_MethodeListElement*) elem2;

  if( *arg1 < arg2->Hash )
  {
    return -1;
  }
  else if( *arg1 > arg2->Hash )
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
