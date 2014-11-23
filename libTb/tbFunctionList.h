/*!
 * <File comment goes here!!>
 * 
 * Copyright (c) 2010 by Lars Elgtvedt Susaas
 */

#pragma once
#include "tbVM.h"

int       tbRegisterFunction(struct tbVM* pVM, tb_method Methode, char* Name);
int       tbReallocMethodeList(struct tbVM* pVM);
tb_method tbFindMethode(struct tbVM* pVM, unsigned int MethodenameHash);

int       tbMethodeElementCompare(const void* elem1, const void* elem2);
int       tbMethodeKeyElementCompare(const void* elem1, const void* elem2);
