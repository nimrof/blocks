
#include "blVM.h"

BLUInt blocks_GetNumInput(HBLOCKSCALL c);
BLUInt blocks_GetNumOutput(HBLOCKSCALL c);

BLResult blocks_PullUint8  (HBLOCKSCALL c, BLUnsigned8*  i);
BLResult blocks_PullInt8   (HBLOCKSCALL c, BLSigned8*    i);
BLResult blocks_PullUint16 (HBLOCKSCALL c, BLUnsigned16* i);
BLResult blocks_PullInt16  (HBLOCKSCALL c, BLSigned16*   i);
BLResult blocks_PullUint32 (HBLOCKSCALL c, BLUnsigned32* i);
BLResult blocks_PullInt32  (HBLOCKSCALL c, BLSigned32*   i);
BLResult blocks_PullFloat32(HBLOCKSCALL c, BLFloat32*    f);
BLResult blocks_PullBool   (HBLOCKSCALL c, BLBool*       b);
BLResult blocks_PullString (HBLOCKSCALL c, BLChar**      s);

BLResult blocks_PushUint8  (HBLOCKSCALL c, BLUnsigned8   i);
BLResult blocks_PushInt8   (HBLOCKSCALL c, BLSigned8     i);
BLResult blocks_PushUint16 (HBLOCKSCALL c, BLUnsigned16  i);
BLResult blocks_PushInt16  (HBLOCKSCALL c, BLSigned16    i);
BLResult blocks_PushUint32 (HBLOCKSCALL c, BLUnsigned32  i);
BLResult blocks_PushInt32  (HBLOCKSCALL c, BLSigned32    i);
BLResult blocks_PushFloat32(HBLOCKSCALL c, BLFloat32     f);
BLResult blocks_PushBool   (HBLOCKSCALL c, BLBool        b);
BLResult blocks_PushString (HBLOCKSCALL c, BLChar*       s);
