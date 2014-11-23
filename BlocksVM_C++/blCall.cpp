#include "blCall.h"

blCallStruct::blCallStruct(blocksVariableList &varList)
{
  vList       = &varList;
  inputIndex  = inputs.end();
  outputIndex = outputs.end();
}
BLResult blCallStruct::pullUint8(BLUnsigned8* i)
{
  if( inputIndex < inputs.end() )
  {
    inputIndex++;
    return vList->getUint8(*inputIndex,i);
  }
  else
  {
    i=0;//TODO: null_ptr in c++11
    return bl_ERROR;
  }
}
BLResult blCallStruct::pullInt8(BLSigned8* i)
{
  if( inputIndex < inputs.end() )
  {
    inputIndex++;
    return vList->getInt8(*inputIndex,i);
  }
  else
  {
    i=0;//TODO: null_ptr in c++11
    return bl_ERROR;
  }
}
BLResult blCallStruct::pullUint16(BLUnsigned16* i)
{
  if( inputIndex < inputs.end() )
  {
    inputIndex++;
    return vList->getUint16(*inputIndex,i);
  }
  else
  {
    i=0;//TODO: null_ptr in c++11
    return bl_ERROR;
  }
}
BLResult blCallStruct::pullInt16(BLSigned16* i)
{
  if( inputIndex < inputs.end() )
  {
    inputIndex++;
    return vList->getInt16(*inputIndex,i);
  }
  else
  {
    i=0;//TODO: null_ptr in c++11
    return bl_ERROR;
  }
}
BLResult blCallStruct::pullUint32(BLUnsigned32* i)
{
  if( inputIndex < inputs.end() )
  {
    inputIndex++;
    return vList->getUint32(*inputIndex,i);
  }
  else
  {
    i=0;//TODO: null_ptr in c++11
    return bl_ERROR;
  }
}
BLResult blCallStruct::pullInt32(BLSigned32* i)
{
  if( inputIndex < inputs.end() )
  {
    inputIndex++;
    return vList->getInt32(*inputIndex,i);
  }
  else
  {
    i=0;//TODO: null_ptr in c++11
    return bl_OK;
  }
}
BLResult blCallStruct::pullFloat32(BLFloat32* f)
{
  if( inputIndex < inputs.end() )
  {
    inputIndex++;
    return vList->getFloat32(*inputIndex,f);
  }
  else
  {
    f=0;//TODO: null_ptr in c++11
    return bl_ERROR;
  }
}
BLResult blCallStruct::pullBool(BLBool* b)
{
  if( inputIndex < inputs.end() )
  {
    inputIndex++;
    return vList->getBool(*inputIndex,b);
  }
  else
  {
    b=0;//TODO: null_ptr in c++11
    return bl_ERROR;
  }
}
BLResult blCallStruct::pullString(std::string* s)
{
  if( inputIndex < inputs.end() )
  {
    inputIndex++;
    return vList->getString(*inputIndex,s);
  }
  else
  {
    s=0;//TODO: null_ptr in c++11
    return bl_ERROR;
  }
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<PUSH
BLResult blCallStruct::pushUint8(BLUnsigned8 i)
{
  if( outputIndex < outputs.end() )
  {
    outputIndex++;
    return vList->setUint8(*outputIndex,i);
  }
  else
  {
    return bl_ERROR;
  }
}
BLResult blCallStruct::pushInt8(BLSigned8 i)
{
  if( outputIndex < outputs.end() )
  {
    outputIndex++;
    return vList->setInt8(*outputIndex,i);
  }
  else
  {
    return bl_ERROR;
  }
}
BLResult blCallStruct::pushUint16(BLUnsigned16 i)
{
  if( outputIndex < outputs.end() )
  {
    outputIndex++;
    return vList->setUint16(*outputIndex,i);
  }
  else
  {
    return bl_ERROR;
  }
}
BLResult blCallStruct::pushInt16(BLSigned16 i)
{
  if( outputIndex < outputs.end() )
  {
    outputIndex++;
    return vList->setInt16(*outputIndex,i);
  }
  else
  {
    return bl_ERROR;
  }
}
BLResult blCallStruct::pushUint32(BLUnsigned32 i)
{
  if( outputIndex < outputs.end() )
  {
    outputIndex++;
    return vList->setUint32(*outputIndex,i);
  }
  else
  {
    return bl_ERROR;
  }
}
BLResult blCallStruct::pushInt32(BLSigned32 i)
{
  if( outputIndex < outputs.end() )
  {
    outputIndex++;
    return vList->setInt32(*outputIndex,i);
  }
  else
  {
    return bl_ERROR;
  }
}
BLResult blCallStruct::pushFloat32(BLFloat32 f)
{
  if( outputIndex < outputs.end() )
  {
    outputIndex++;
    return vList->setFloat32(*outputIndex,f);
  }
  else
  {
    return bl_ERROR;
  }
}
BLResult blCallStruct::pushBool(BLBool b)
{
  if( outputIndex < outputs.end() )
  {
    outputIndex++;
    return vList->setBool(*outputIndex,b);
  }
  else
  {
    return bl_ERROR;
  }
}
BLResult blCallStruct::pushString(std::string s)
{
  if( outputIndex < outputs.end() )
  {
    outputIndex++;
    return vList->setString(*outputIndex,s);
  }
  else
  {
    return bl_ERROR;
  }
}
