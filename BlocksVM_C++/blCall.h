/*!
 * <File comment goes here!!>
 *
 * Copyright (c) 2010 by Lars Elgtvedt Susaas
 */

#pragma once
#include <string>
#include <vector>

#include "BlocksType.h"
#include "blVariableList.h"

typedef struct blCallStruct* HBLOCKSCALL;

typedef BLResult (*bl_function)(HBLOCKSCALL CallData);

class blCallStruct
{
  public:
    blCallStruct(blocksVariableList &varList);
    BLResult pullUint8  (BLUnsigned8*  i);
    BLResult pullInt8   (BLSigned8*    i);
    BLResult pullUint16 (BLUnsigned16* i);
    BLResult pullInt16  (BLSigned16*   i);
    BLResult pullUint32 (BLUnsigned32* i);
    BLResult pullInt32  (BLSigned32*   i);
    BLResult pullFloat32(BLFloat32*    f);
    BLResult pullBool   (BLBool*       b);
    BLResult pullString (std::string*  s);

    BLResult pushUint8  (BLUnsigned8   i);
    BLResult pushInt8   (BLSigned8     i);
    BLResult pushUint16 (BLUnsigned16  i);
    BLResult pushInt16  (BLSigned16    i);
    BLResult pushUint32 (BLUnsigned32  i);
    BLResult pushInt32  (BLSigned32    i);
    BLResult pushFloat32(BLFloat32     f);
    BLResult pushBool   (BLBool        b);
    BLResult pushString (std::string   s);
  private:
    blocksVariableList*                        vList;
    bl_function                                cfunction;

    std::vector<blCallStruct*>                 inputDependency;
    std::vector<blCallStruct*>                 outputDependency;

    std::vector<BLNumVariable>                 inputs;
    std::vector<BLNumVariable>                 outputs;

    std::vector<BLNumVariable>::const_iterator inputIndex;
    std::vector<BLNumVariable>::const_iterator outputIndex;
};
