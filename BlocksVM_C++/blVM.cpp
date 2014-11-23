/*!
 * <File comment goes here!!>
 * 
 * Copyright (c) 2010 by Lars Elgtvedt Susaas
 */

#include "blVM.h"
#include "blFunctionList.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/*!
 * \brief
 * Check if the methode is ready to be called or has been called.
 *
 * \param pMethode
 * Pointer to the methodecall structur that will be checked.
 *
 * \param Iterator
 * Current script iterator (incremental run counter).
 *
 * \returns
 * 1 if the function is ready to be called, 0 if its not ready.
 *
 * \remarks
 * Internal methode and should not be user directly.
 *
 *//*
int tbIsMethodeReadyForCall(struct tbMethodeCall* pMethode, const unsigned int Iterator)
{
  unsigned int i;
  unsigned Result = 1;

  if(pMethode->Iterator == Iterator)
  {
    return 0;
  }

  for(i = 0; i < pMethode->NumInput; i++)
  {
    if( pMethode->Input[i]->Iterator == Iterator)
    {
      Result *= 1;
    }
    else
    {
      Result *= 0;
    }
  }
  return Result;
}*/
/*!
 * \brief
 * Runs the script once.
 *
 * \param pScript
 * Pointer to script that will run once.
 *
 * \remarks
 * Internal methode and should not be user directly.
 *
 * \see
 * tbRunVMOneIteration
 *//*
void tbRunVMScriptOneIteration(struct tbScript* pScript)
{
  unsigned int MethodeCalled = 0;
  unsigned int i;
  struct tbMethodeCall* pMethode;

  pScript->Iterator++;

  while (MethodeCalled < pScript->NumMethodeCall)
  {
    for(i = 0; i < pScript->NumMethodeCall; i++)
    {
      pMethode = &pScript->MethodeCall[i];
      if ( tbIsMethodeReadyForCall(pMethode,pScript->Iterator) )
      {
        tbCallMethode(pMethode,pScript->Iterator);
        MethodeCalled++;
      }
    }
  }
}*/
/*!
 * \brief
 * Run all the scripts in the vm once.
 *
 * \param pVM
 * Pointer to VM that will run once.
 *
 * \see
 * tbRunVMScriptOneIteration
 *//*
void tbRunVMOneIteration(struct tbVM* pVM)
{
  unsigned int i;
  for (i = 0; i < pVM->NumScript; i++)
  {
    tbRunVMScriptOneIteration( &pVM->Script[i] );
  }
}*/
/*!
 * \brief
 * Check if the methode is ready to be called or has been called.
 *
 * \param pScript
 * Pointer to script that will run once.
 *
 * \returns
 * 1 if the function is ready to be called, 0 if its not ready.
 *
 * \remarks
 * Internal methode and should not be user directly.
 *
 * \see
 * tbRunVMOneIteration
 */
