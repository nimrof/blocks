
#include "BlocksType.h"

typedef BLResult (*BLFUNCTION)(HBLOCKSVM);

HBLOCKSVM block_open(BLChar* Buffer, BLUnsigned16 BufferSize);
void block_close(HBLOCKSVM vm);
typedef Integer (*BLFUNCTION)(HBCALL);

BLNumVariable blocks_GetNumInput(HBCALL);
BLNumVariable blocks_GetNumOutput(HBCALL);

BLResult blocks_PullUint8(HBCALL,   BLUnsigned8*  i);
BLResult blocks_PullInt8(HBCALL,    BLSigned8*    i);
BLResult blocks_PullUint16(HBCALL,  BLUnsigned16* i);
BLResult blocks_PullInt16(HBCALL,   BLSigned16*   i);
BLResult blocks_PullUint32(HBCALL,  BLUnsigned32* i);
BLResult blocks_PullInt32(HBCALL,   BLSigned32*   i);
BLResult blocks_PullFloat32(HBCALL, BLFloat32*    f);
BLResult blocks_PullBool(HBCALL,    BLBool*       b);
BLResult blocks_PullString(HBCALL,  BLChar**      s);

BLResult blocks_PushUint8(HBCALL,   BLUnsigned8  i);
BLResult blocks_PushInt8(HBCALL,    BLSigned8    i);
BLResult blocks_PushUint16(HBCALL,  BLUnsigned16 i);
BLResult blocks_PushInt16(HBCALL,   BLSigned16   i);
BLResult blocks_PushUint32(HBCALL,  BLUnsigned32 i);
BLResult blocks_PushInt32(HBCALL,   BLSigned32   i);
BLResult blocks_PushFloat32(HBCALL, BLFloat32    f);
BLResult blocks_PushBool(HBCALL,    BLBool       b);
BLResult blocks_PushString(HBCALL,  BLChar*      s);

BLResult block_LoadScriptBuffer(const BLChar Buffer);
BLResult block_RegisterBlock(const BLChar Buffer);

/*
[4cc][data-ver][32bit conf][num call][hash][numi][numo][input][output]
[bit-field of datatypes][num type-n][num type-n+1][num type-string (if any)][size string1 (max 255)]
[bit-field of const datatypes][num type-n][index + value for n][num type-n+1][index + value for n+1][num type-string (if any)][size string1 (max 255)]
*/