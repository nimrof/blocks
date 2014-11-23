/*!
 * <File comment goes here!!>
 * 
 * Copyright (c) 2010 by Lars Elgtvedt Susaas
 */

#include "tbVM.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

const unsigned long INTEGER_HASH = 0xBA6C2A10; //3127650832 //TODO: Check..need inv?
const unsigned long BOOLEAN_HASH = 0x41327C73; //1093827699 //TODO: Check..need inv?
const unsigned long FLOAT_HASH   = 0xAACB0EAE; //2865434286 //TODO: Check..need inv?
const unsigned long CSTRING_HASH = 0x0CE34DDD; // 216223197 //TODO: Check..need inv?

/*!
 * \brief
 * Creates a new VM
 *
 * \returns
 * pointer to a new vm or NULL on error.
 *
 */
struct tbVM* CreateVM(void)
{
  struct tbVM* newVM = malloc( sizeof(struct tbVM) );

  newVM->Methodes.ListSize    = DefaultMethodeListSize;
  newVM->Methodes.TopIndex    = 0; 
  newVM->Methodes.MethodeList = calloc(newVM->Methodes.ListSize, sizeof(newVM->Methodes.MethodeList[0]));

  if( newVM->Methodes.MethodeList == NULL )
  {
    free( newVM->Methodes.MethodeList );
    return NULL;
  }
  else
  {
    return newVM;
  }
}
/*!
 * \brief
 * Calls the methode
 *
 * \param pMethode
 * Pointer to the methodecall structur that will be called.
 *
 * \param Iterator
 * Current script iterator (incremental run counter).
 *
 * \remarks
 * Internal methode and should not be user directly.
 *
 */
void tbCallMethode(struct tbMethodeCall* pMethode, const unsigned int Iterator)
{
  unsigned int i;
  struct Parameter** Input;
  struct Parameter** Output;

  Input  = malloc(pMethode->NumInput  * sizeof(struct Parameter*) );//should pre-alloc?
  if(Input == NULL)
  {
    return;
  }

  Output = malloc(pMethode->NumOutput * sizeof(struct Parameter*) );//should pre-alloc?
  if(Input == NULL)
  {
    return;
  }

  for(i = 0; i < pMethode->NumInput; i++)
  {
    Input[i]  = &pMethode->Input[i]->ParameterData;
  }

  for(i = 0; i < pMethode->NumOutput; i++)
  {
    Output[i] = &pMethode->Output[i]->ParameterData;
  }

  pMethode->Func(Input,pMethode->NumInput,Output,pMethode->NumOutput);

  for(i = 0; i < pMethode->NumOutput; i++)
  {
    pMethode->Output[i]->Iterator = Iterator;
  }
  pMethode->Iterator = Iterator;

  free(Input);
  free(Output);
}
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
 */
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
}
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
 */
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
}
/*!
 * \brief
 * Run all the scripts in the vm once.
 *
 * \param pVM
 * Pointer to VM that will run once.
 *
 * \see
 * tbRunVMScriptOneIteration
 */
void tbRunVMOneIteration(struct tbVM* pVM)
{
  unsigned int i;
  for (i = 0; i < pVM->NumScript; i++)
  {
    tbRunVMScriptOneIteration( &pVM->Script[i] );
  }
}
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
int tbSetIntegerOutput(struct Parameter** Output, unsigned int NumOutput, unsigned int Num, int Value)
{
  if(NumOutput > Num)
  {
    if(Output[Num]->HashOfType == INTEGER_HASH)
    {
      Output[Num]->Value.Integer = Value;
      return TB_OK;
    }
  }
  return TB_ERROR;
}
int tbSetBooleanOutput(struct Parameter** Output, unsigned int NumOutput, unsigned int Num, enum tbBoolean Value)
{
  if(NumOutput > Num)
  {
    if(Output[Num]->HashOfType == BOOLEAN_HASH)
    {
      Output[Num]->Value.Boolean = Value;
      return TB_OK;
    }
  }
  return TB_ERROR;
}
int tbSetFloatingOutput(struct Parameter** Output, unsigned int NumOutput, unsigned int Num, float Value)
{
  if(NumOutput > Num)
  {
    if(Output[Num]->HashOfType == FLOAT_HASH) 
    {
      Output[Num]->Value.Floating = Value;
      return TB_OK;
    }
  }
  return TB_ERROR;
}
int tbSetStringOutput(struct Parameter** Output, unsigned int NumOutput, unsigned int Num, char* Value)
{
  if(NumOutput > Num)
  {
    if(Output[Num]->HashOfType == CSTRING_HASH)
    {
      Output[Num]->Value.cString = Value;
      return TB_OK;
    }
  }
  return TB_ERROR;
}

int tbSetCustomTypeOutput(struct Parameter** Output, unsigned int NumOutput, unsigned int Num, unsigned int Type, void* Value)
{
  if(NumOutput > Num)
  {
    if(Output[Num]->HashOfType == Type)
    {
      Output[Num]->Value.GenerincPointer = Value;
      return TB_OK;
    }
  }
  return TB_ERROR;
}
//Spaceer
int tbGetIntegerInput(struct Parameter** Input, unsigned int NumInput, unsigned int Num, int* Value)
{
  if(NumInput > Num)
  {
    if(Input[Num]->HashOfType == INTEGER_HASH)
    {
      *Value = Input[Num]->Value.Integer;
      return TB_OK;
    }
  }
  return TB_ERROR;
}
int tbGetBooleanInput(struct Parameter** Input, unsigned int NumInput, unsigned int Num, enum tbBoolean* Value)
{
  if(NumInput > Num)
  {
    if(Input[Num]->HashOfType == BOOLEAN_HASH)
    {
      *Value = Input[Num]->Value.Boolean;
      return TB_OK;
    }
  }
  return TB_ERROR;
}
int tbGetFloatingInput(struct Parameter** Input, unsigned int NumInput, unsigned int Num, float* Value)
{
  if(NumInput > Num)
  {
    if(Input[Num]->HashOfType == FLOAT_HASH)
    {
      *Value = Input[Num]->Value.Floating;
      return TB_OK;
    }
  }
  return TB_ERROR;
}
int tbGetStringInput(struct Parameter** Input, unsigned int NumInput, unsigned int Num, char** Value)
{
  if(NumInput > Num)
  {
    if(Input[Num]->HashOfType == CSTRING_HASH)
    {
      *Value = Input[Num]->Value.cString;
      return TB_OK;
    }
  }
  return TB_ERROR;
}
int tbGetCustomTypeInput(struct Parameter** Input, unsigned int NumInput, unsigned int Num, unsigned int Type, void** Value)
{
  if(NumInput > Num)
  {
    if(Input[Num]->HashOfType == Type)
    {
      *Value = Input[Num]->Value.GenerincPointer;
      return TB_OK;
    }
  }
  return TB_ERROR;
}
