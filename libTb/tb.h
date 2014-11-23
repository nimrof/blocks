/*!
 * <File comment goes here!!>
 * 
 * Copyright (c) 2010 by Lars Elgtvedt Susaas
 */

#pragma once

#define TB_ERROR 0
#define TB_FALSE 0
#define TB_OK    1

enum tbBoolean
{
  tbFALSE,
  tbTRUE
};
union RawValue
{
  int            Integer;
  enum tbBoolean Boolean;
  float          Floating;
  char*          cString;
  void*          GenerincPointer;
};
struct Parameter
{
  unsigned int HashOfType;
  union RawValue Value;
};
struct ParameterData
{
  struct Parameter ParameterData;
  unsigned int	   Iterator;
};

typedef int (*tb_method)(struct Parameter** Input,
						 int NumInput,
						 struct Parameter** Output,
						 int NumOutput);
struct tbMethodeCall
{     
  unsigned int           NumInput;
  unsigned int           NumOutput;
  struct ParameterData** Input;
  struct ParameterData** Output;
  tb_method              Func;
  unsigned int	         Iterator;
};

struct tb_MethodeListElement
{
  unsigned int Hash;
  tb_method    Methode;
};

struct tb_MethodeList
{
  struct tb_MethodeListElement* MethodeList;
  int                           ListSize;
  int                           TopIndex;
};

struct tbScript
{
  struct ParameterData* Parameters;
  unsigned int	        NumParam;
  struct tbMethodeCall* MethodeCall;
  unsigned int	        NumMethodeCall;
  unsigned int	        Iterator;
};

struct tbVM
{
  struct tb_MethodeList Methodes;
  struct tbScript*      Script;
  unsigned int	        NumScript;
};
