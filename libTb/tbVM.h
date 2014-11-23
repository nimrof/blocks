/*!
 * <File comment goes here!!>
 * 
 * Copyright (c) 2010 by Lars Elgtvedt Susaas
 */

#pragma once
#include "tb.h"

#define DefaultMethodeListSize 256

struct tbVM* CreateVM(void);
void tbRunVMOneIteration(struct tbVM* pVM);

int tbSetIntegerOutput(struct Parameter** Output, unsigned int NumOutput, unsigned int Num, int Value);
int tbSetBooleanOutput(struct Parameter** Output, unsigned int NumOutput, unsigned int Num, enum tbBoolean Value);
int tbSetFloatingOutput(struct Parameter** Output, unsigned int NumOutput, unsigned int Num, float Value);
int tbSetStringOutput(struct Parameter** Output, unsigned int NumOutput, unsigned int Num, char* Value);
int tbSetCustomTypeOutput(struct Parameter** Output, unsigned int NumOutput, unsigned int Num, unsigned int Type, void* Value);

int tbGetIntegerInput(struct Parameter** Input, unsigned int NumInput, unsigned int Num, int* Value);
int tbGetBooleanInput(struct Parameter** Input, unsigned int NumInput, unsigned int Num, enum tbBoolean* Value);
int tbGetFloatingInput(struct Parameter** Input, unsigned int NumInput, unsigned int Num, float* Value);
int tbGetStringInput(struct Parameter** Input, unsigned int NumInput, unsigned int Num, char** Value);
int tbGetCustomTypeInput(struct Parameter** Input, unsigned int NumInput, unsigned int Num, unsigned int Type, void** Value);
