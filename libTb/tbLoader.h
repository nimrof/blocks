/*!
 * <File comment goes here!!>
 * 
 * Copyright (c) 2010 by Lars Elgtvedt Susaas
 */

#include "tb.h"
#include "tbConf.h"

#if defined(FileSupport)

int tbLoadFile(struct tbVM* pVM, const char* FilePath);

#endif

int tbLoadBuffer(struct tbVM* pVM, const char* Buffer, long BufferSize);
