/*!
 * This file holds the source code for loading scripts eather from file or memory.
 * 
 * Copyright (c) 2010 by Lars Elgtvedt Susaas
 */

#include "tbLoader.h"
#include "tbConf.h"
#include <stdlib.h> 
#include <string.h>
#include "tbFunctionList.h"

#if defined(FileSupport)
#include <stdio.h>
/*!
 * \brief
 * Returns the size of a open file.
 *
 * \param fFile
 * File handel to the file its size will be returnet.
 *
 * \returns
 * File size
 *
 * \remarks
 * *Internal* File position will be set to the start of the file.
 *
 * \see
 * tbLoadFile FileSupport
 */
long tbGetFileSize(FILE* fFile)
{
  long Size;
  fseek(fFile, 0L, SEEK_END);
  Size = ftell(fFile);
  fseek(fFile, 0L, SEEK_SET);
  return Size;
}
/*!
 * \brief
 * Returns the size of a open file.
 *
 * \param pVM
 * The virtual machine to load the scripts into.
 *
 * \param FilePath
 * The path to the file.
 *
 * \returns
 * TB_ERROR on any error in loading the file, TB_OK if not.
 *
 * \remarks
 * File position will be set to the start of the file.
 *
 * \see
 * tbLoadFile tbBufferRead FileSupport 
 */
int tbLoadFile(struct tbVM* pVM, const char* FilePath)
{
  long FileSize;
  char* RawFileBuffer;
  FILE* fFile;
  const char FCC[] = "BCCF";
  fFile = fopen( FilePath, "r" );
  if( fFile == NULL)
  {
    return TB_ERROR;
  }
  FileSize = tbGetFileSize(fFile);

  RawFileBuffer = malloc(FileSize);
  if( RawFileBuffer == NULL)
  {
    fclose(fFile);
    return TB_ERROR;
  }

  if (fread(RawFileBuffer,FileSize,1,fFile) == 0 )
  {
    //Read error.... Need this?
    fclose(fFile);
	return TB_ERROR;
  }

  if( memcmp(FCC,RawFileBuffer,sizeof(FCC) -1) != 0)
  {
    //This does not look like a file.
      fclose(fFile);
	  return TB_ERROR;
  }
  fclose(fFile);

  return tbLoadBuffer(pVM, &RawFileBuffer[ sizeof(FCC) -1 ], FileSize - (sizeof(FCC) -1) );
}
#endif
/*!
 * \brief
 * Helper function to make reading of "memoryfile" safer.
 *
 * \param Destination
 * Pointer to the area to write the data from the buffer to.
 *
 * \param ElementSize
 * Size of the element to read from the buffer.
 *
 * \param BufferSize
 * Total size of the buffer.
 *
 * \param Buffer
 * Pointer to the buffer.
 *
 * \param BufferPointer
 * Offset of the buffer to the current buffer position.
 *
 * \returns
 * TB_ERROR if the the read will go outside the buffer, TB_OK if not.
 *
 * \see
 * tbLoadMethodeFromBuffer
 */
int tbBufferRead(void* Destination,unsigned int ElementSize, const long BufferSize, const char* Buffer, unsigned int* BufferPointer)
{
  if( (*BufferPointer + ElementSize) > (unsigned int)BufferSize)
  {
    //reading outsize the buffer.
    return TB_ERROR;
  }
  else
  {
    memcpy(Destination,&Buffer[*BufferPointer],ElementSize);
    *BufferPointer += ElementSize;
    return TB_OK;
  }
}
/*!
 * \brief
 * Reads a methodecall from buffer.
 *
 * \param pVM
 * The virtual machine that holds the scripts.
 *
 * \param pScript
 * Script to load the methode call into.
 *
 * \param Buffer
 * Pointer to the buffer.
 *
 * \param BufferSize
 * Total size of the buffer.
 *
 * \param BufferPointer
 * Offset of the buffer to the current buffer position.
 *
 * \param tbMethodeCall
 * Pointer the the methode call structure to put the data into.
 *
 * \returns
 * TB_ERROR on error, TB_OK if none is found.
 *
 * \see
 * tbLoadScriptFromBuffer
 */
int tbLoadMethodeFromBuffer(struct tbVM* pVM, struct tbScript* pScript, const char* Buffer, const long BufferSize, unsigned int* BufferPointer, struct tbMethodeCall* Methode)
{
  unsigned int MethodeHash;
  unsigned int VariableIndex;
  unsigned int i;
  
  Methode->Iterator = 0;

  if( tbBufferRead(&MethodeHash,sizeof(MethodeHash),BufferSize,Buffer,BufferPointer) == 0)
  {
    return TB_ERROR;
  }
  else
  {
    Methode->Func = tbFindMethode(pVM,MethodeHash);
    if (Methode->Func == NULL)
    {
      return TB_ERROR;
    }
  }

  if( tbBufferRead(&Methode->NumInput,sizeof(Methode->NumInput),BufferSize,Buffer,BufferPointer) == 0)
  {
    return TB_ERROR;
  }
  else
  {
    Methode->Input = malloc( sizeof(Methode->Input) * Methode->NumInput);
    if(Methode->Input == NULL)
    {
      return TB_ERROR;
    }
  }

  if( tbBufferRead(&Methode->NumOutput,sizeof(Methode->NumOutput),BufferSize,Buffer,BufferPointer) == 0)
  {
    return TB_ERROR;
  }
  else
  {
    Methode->Output = malloc( sizeof(Methode->Output) * Methode->NumOutput);
    if(Methode->Output == NULL)
    {
      return TB_ERROR;
    }
  }

  for(i = 0; i < Methode->NumInput; i++)
  {
    tbBufferRead(&VariableIndex,sizeof(VariableIndex),BufferSize,Buffer,BufferPointer);
    if( VariableIndex > pScript->NumParam )
    {
      return TB_ERROR;
    }
    else
    {
      Methode->Input[i] = &pScript->Parameters[VariableIndex];
    }
  }

  for(i = 0; i < Methode->NumOutput; i++)
  {
    tbBufferRead(&VariableIndex,sizeof(VariableIndex),BufferSize,Buffer,BufferPointer);
    if( VariableIndex > pScript->NumParam )
    {
      return TB_ERROR;
    }
    else
    {
      Methode->Output[i] = &pScript->Parameters[VariableIndex];
    }
  }
  return TB_OK;
}
/*!
 * \brief
 * Reads a script from buffer..
 *
 * \param pVM
 * The virtual machine that holds the scripts.
 *
 * \param Buffer
 * Pointer to the buffer.
 *
 * \param BufferSize
 * Total size of the buffer.
 *
 * \param BufferPointer
 * Offset of the buffer to the current buffer position.
 *
 * \param pScript
 * Pointer the the script structure to put the data into.
 *
 * \returns
 * TB_ERROR on error, TB_OK if none is found.
 *
 * \see
 * tbLoadBuffer
 */
int tbLoadScriptFromBuffer(struct tbVM* pVM, const char* Buffer, const long BufferSize, unsigned int* BufferPointer, struct tbScript* pScript)
{
  unsigned int i;

  pScript->Iterator = 0;

  if(tbBufferRead(&pScript->NumParam,sizeof(pScript->NumParam),BufferSize,Buffer,BufferPointer) == 0)
  {
    return TB_ERROR;
  }

  pScript->Parameters = malloc( pScript->NumParam * sizeof(*pScript->Parameters) );
  if( pScript->Parameters == NULL )
  {
    return TB_ERROR;
  }

  for (i = 0; i < pScript->NumParam; i++)
  {
	if(tbBufferRead(&pScript->Parameters[i].ParameterData.HashOfType,sizeof(pScript->Parameters[i].ParameterData.HashOfType),BufferSize,Buffer,BufferPointer) == 0)
	{
      return TB_ERROR;
	}
  }

  if(tbBufferRead(&pScript->NumMethodeCall,sizeof(pScript->NumMethodeCall),BufferSize,Buffer,BufferPointer) == 0)
  {
    return TB_ERROR;
  }

  pScript->MethodeCall = malloc(pScript->NumMethodeCall * sizeof(*pScript->MethodeCall));
  if( pScript->MethodeCall == NULL )
  {
    return TB_ERROR;
  }

  for (i = 0; i < pScript->NumMethodeCall; i++)
  {
    if( tbLoadMethodeFromBuffer(pVM,pScript, Buffer,BufferSize,BufferPointer,&pScript->MethodeCall[i]) == TB_ERROR)
	{
      return TB_ERROR;
	}
  }
  return TB_OK;
}
/*!
 * \brief
 * Reads script(s) from buffer.
 *
 * \param pVM
 * The virtual machine that will hold the script(s).
 *
 * \param Buffer
 * Pointer to the buffer.
 *
 * \param BufferSize
 * Total size of the buffer.
 *
 * \returns
 * TB_ERROR on error, TB_OK if none is found.
 *
 * \remarks
 * Currently there is undefined what will hapend if the vm is not empty (except for registerd methodes.
 *
 * \see
 * tbLoadFile
 */
int tbLoadBuffer(struct tbVM* pVM, const char* Buffer, long BufferSize)
{
  unsigned int BufferPointer = 0;
  unsigned int i;

  if( tbBufferRead(&pVM->NumScript,sizeof(pVM->NumScript),BufferSize,Buffer,&BufferPointer) == TB_ERROR )
  {
    return TB_ERROR;
  }

  pVM->Script = malloc(pVM->NumScript * sizeof(*pVM->Script));
  if( pVM->Script == NULL )
  {
    return TB_ERROR;
  }

  for (i = 0; i < pVM->NumScript; i++)
  {
    if( tbLoadScriptFromBuffer(pVM,Buffer,BufferSize,&BufferPointer,&pVM->Script[i]) == TB_ERROR )
	{
      return TB_ERROR;
	}
  }
  return TB_OK;
}
