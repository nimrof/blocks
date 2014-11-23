/*!
 * Source for handeling methode registering and seaching
 * 
 * Copyright (c) 2010 by Lars Elgtvedt Susaas
 */

#include "blFunctionList.h"
#include "blHash.h"
#include "blVM.h"
#include <string.h>

#include <stdlib.h>

//file internal functions
static int blFunctionElementCompare    (const void* elem1, const void* elem2);
static int blFunctionKeyElementCompare (const void* elem1, const void* elem2);

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
BLResult blFindFunction(HBLOCKSVM v, BLHash nameHash, bl_function* pFunction)
{
  struct blFunctionListElement* listEntry;

  listEntry = (struct blFunctionListElement*)bsearch(&nameHash,v->buffer,v->numFunctions,sizeof(struct blFunctionListElement),blFunctionKeyElementCompare);

  if(listEntry)
  {
    *pFunction = listEntry->function;
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
BLResult blRegisterFunction(HBLOCKSVM v, bl_function function, char* name)
{
  BLHash functionIndex;

  if(v->hasLoadedScript)
  {
    //Not allowed to register functions after script is loader.....simpler that way
    return bl_ERROR;
  }
  else
  {
    //Check to see that we have space for one more function
    if( (v->numFunctions+1)*sizeof(struct blFunctionListElement) > v->bufferSize)
    {
      v->numFunctions++;
      functionIndex = v->numFunctions;
      v->functionList[functionIndex].hash     = blHash(name,strlen(name));
      v->functionList[functionIndex].function = function;
    }
    else
    {
     //not enought memory to register function with %name
     return bl_ERROR;
    }
  }

   qsort(v->functionList,v->numFunctions,sizeof(struct blFunctionListElement), blFunctionElementCompare);

  return bl_OK;
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
static int blFunctionElementCompare( const void* elem1, const void* elem2 )
{
  const struct blFunctionListElement* arg1 = (const struct blFunctionListElement*) elem1;
  const struct blFunctionListElement* arg2 = (const struct blFunctionListElement*) elem2;

  if( arg1->hash < arg2->hash )
  {
    return -1;
  }
  else if( arg1->hash > arg2->hash )
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
 * blFindMethode blMethodeKeyElementCompare
 */
static int blFunctionKeyElementCompare( const void* elem1, const void* elem2 )
{
  const unsigned int* arg1                = (const unsigned int*) elem1;
  const struct blFunctionListElement* arg2 = (const struct blFunctionListElement*) elem2;

  if( *arg1 < arg2->hash )
  {
    return -1;
  }
  else if( *arg1 > arg2->hash )
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
