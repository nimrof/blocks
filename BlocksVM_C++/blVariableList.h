/*!
 * <File comment goes here!!>
 *
 * Copyright (c) 2010 by Lars Elgtvedt Susaas
 */

#pragma once
#include <string>
#include <vector>

#include "BlocksType.h"


class blocksVariableList
{
  public:
    BLResult getUint8  (BLNumVariable index, BLUnsigned8*  i);
    BLResult getInt8   (BLNumVariable index, BLSigned8*    i);
    BLResult getUint16 (BLNumVariable index, BLUnsigned16* i);
    BLResult getInt16  (BLNumVariable index, BLSigned16*   i);
    BLResult getUint32 (BLNumVariable index, BLUnsigned32* i);
    BLResult getInt32  (BLNumVariable index, BLSigned32*   i);
    BLResult getFloat32(BLNumVariable index, BLFloat32*    f);
    BLResult getBool   (BLNumVariable index, BLBool*       b);
    BLResult getString (BLNumVariable index, std::string*  s);

    BLResult setUint8  (BLNumVariable index, BLUnsigned8   i);
    BLResult setInt8   (BLNumVariable index, BLSigned8     i);
    BLResult setUint16 (BLNumVariable index, BLUnsigned16  i);
    BLResult setInt16  (BLNumVariable index, BLSigned16    i);
    BLResult setUint32 (BLNumVariable index, BLUnsigned32  i);
    BLResult setInt32  (BLNumVariable index, BLSigned32    i);
    BLResult setFloat32(BLNumVariable index, BLFloat32     f);
    BLResult setBool   (BLNumVariable index, BLBool        b);
    BLResult setString (BLNumVariable index, std::string   s);
  private:
    std::vector <BLUnsigned8 >                             b08List;
    std::vector <BLUnsigned16>                             b16List;
    std::vector <BLUnsigned32>                             b32List;
    std::vector < std::pair<BLNumVariable,BLNumVariable> > ArrayList;
    std::vector < std::string >                            StringList;
};
