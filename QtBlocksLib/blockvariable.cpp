#include <QObject>

#include "exceptions.h"

#include "blockvariable.h"

namespace blocks
{

blockVariable::blockVariable()
{
  type   = UNDEFINED;
}
blockVariable::blockVariable(const QString type, const QString value)
{
  this->type = stringToDatatype(type);
  stringToData(value);
}
blockVariable::blockVariable(const dataType varType, const QString strData)
{
  type   = varType;
  stringToData(strData);
}
blockVariable::blockVariable(const bool b)
{
  type   = BOOLEAN;
  data.b = b;
}
blockVariable::blockVariable(const qint8 i)
{
  type    = INT_8;
  data.i8 = i;
}
blockVariable::blockVariable(const qint16 i)
{
  type     = INT_16;
  data.i16 = i;
}
blockVariable::blockVariable(const qint32 i)
{
  type     = INT_32;
  data.i32 = i;
}
blockVariable::blockVariable(const qint64 i)
{
  type     = INT_64;
  data.i64 = i;
}
blockVariable::blockVariable(const quint8 i)
{
  type     = UINT_8;
  data.ui8 = i;
}
blockVariable::blockVariable(const quint16 i)
{
  type      = UINT_16;
  data.ui16 = i;
}
blockVariable::blockVariable(const quint32 i)
{
  type      = UINT_32;
  data.ui32 = i;
}
blockVariable::blockVariable(const quint64 i)
{
  type      = UINT_64;
  data.ui64 = i;
}
blockVariable::blockVariable(const float f)
{
  type     = FLOAT_32;
  data.f32 = f;
}
blockVariable::blockVariable(const double f)
{
  type = FLOAT_64;
  data.f64 = f;
}
dataType blockVariable::getDataType() const
{
  return type;
}
dataType blockVariable::stringToDatatype(const QString str)
{
  if(str == "RUN")
    return RUN;
  else if(str == "BOOLEAN")
    return BOOLEAN;
  else if(str == "INT_8")
    return INT_8;
  else if(str == "INT_16")
    return INT_16;
  else if(str == "INT_32")
    return INT_32;
  else if(str == "INT_64")
    return INT_64;
  else if(str == "UINT_8")
    return UINT_8;
  else if(str == "UINT_16")
    return UINT_16;
  else if(str == "UINT_32")
    return UINT_32;
  else if(str == "UINT_64")
    return UINT_64;
  else if(str == "FLOAT_32")
    return FLOAT_32;
  else if(str == "FLOAT_64")
    return FLOAT_64;
  else if(str == "ARRAY")
    return ARRAY;
  else if(str == "STRUCT")
    return STRUCT;
  else if(str == "STRING")
    return STRING;
  else
    throw xml_logic_error(QString(QObject::tr("%1 is of unknow type")).arg(str));
}
QString blockVariable::datatypeToString(const dataType type)
{
  switch(type)
  {
    case BOOLEAN:
      return QString("BOOLEAN");
    case INT_8:
      return QString("INT_8");
    case INT_16:
      return QString("INT_16");
    case INT_32:
      return QString("INT_32");
    case INT_64:
      return QString("INT_64");
    case UINT_8:
      return QString("UINT_8");
    case UINT_16:
      return QString("UINT_16");
    case UINT_32:
      return QString("UINT_32");
    case UINT_64:
      return QString("UINT_64");
    case FLOAT_32:
      return QString("FLOAT_32");
    case FLOAT_64:
      return QString("FLOAT_64");
    case ARRAY:
      return QString("ARRAY");
    case STRUCT:
      return QString("STRUCT");
    case STRING:
      return QString("STRING");
    default:
      throw "unknow type";
  }
}
QString blockVariable::dataToString() const
{
  switch(type)
  {
    case BOOLEAN:
      return QString("%1").arg(data.b);
    case INT_8:
      return QString("%1").arg(data.i8);
    case INT_16:
      return QString("%1").arg(data.i16);
    case INT_32:
      return QString("%1").arg(data.i32);
    case INT_64:
      return QString("%1").arg(data.i64);
    case UINT_8:
      return QString("%1").arg(data.ui8);
    case UINT_16:
      return QString("%1").arg(data.ui16);
    case UINT_32:
      return QString("%1").arg(data.ui32);
    case UINT_64:
      return QString("%1").arg(data.ui64);
    case FLOAT_32:
      return QString("%1").arg(data.f32);
    case FLOAT_64:
      return QString("%1").arg(data.f64);
    default:
      return QString(QObject::tr("ERROR: default in  blockVariable::dataToString"));
      break;
  }
}
void blockVariable::stringToData(const QString strData)
{
  bool conversionResult;
  switch(type)
  {
    case BOOLEAN:
      if( (strData == QString("true")) || (strData == QString("false")) )
      {
        data.b = strData == QString("true") ? true:false;
      }
      else
      {
        throw conversion_error(strData,QObject::tr("not a valid boolean ('true' or 'false') ") );
      }
      break;
    case INT_8:
      {
        short rawValue = strData.toShort(&conversionResult);
        if(conversionResult)
        {
          qint8 i8 = rawValue & 0xFF;
          if( i8 == rawValue )
          {
            data.i8 = rawValue;
          }
          else
          {
            throw conversion_error(strData,QObject::tr("to high or low value for int8(8 bit integer") );
          }
        }
        else
        {
         throw conversion_error(strData,QObject::tr("not a valid integer") );
        }
      }
      break;
    case INT_16:
      {
        short rawValue = strData.toShort(&conversionResult);
        if(!conversionResult)
        {
          throw conversion_error(strData,QObject::tr("not a valid int16(16 bit integer)") );
        }
        data.i16 = rawValue;
      }
      break;
    case INT_32:
      {
        long rawValue = strData.toLong(&conversionResult);
        if(!conversionResult)
        {
          throw conversion_error(strData,QObject::tr("not a valid int32(32 bit integer)") );
        }
        data.i32 = rawValue;
      }
      break;
    case INT_64:
      {
        qlonglong rawValue = strData.toLongLong(&conversionResult);
        if(!conversionResult)
        {
          throw conversion_error(strData,QObject::tr("not a valid int64(64 bit integer)") );
        }
        data.i64 = rawValue;
      }
      break;
    case UINT_8:
      {
        ushort rawValue = strData.toUShort(&conversionResult);
        if(conversionResult)
        {
          quint8 ui8 = rawValue & 0xFF;
          if( ui8 == rawValue )
          {
            data.ui8 = rawValue;
          }
          else
          {
            throw conversion_error(strData,QObject::tr("to high value for int8(8 bit integer") );
          }
        }
        else
        {
         throw conversion_error(strData,QObject::tr("not a valid integer") );
        }
      }
      break;
    case UINT_16:
      {
        ushort rawValue = strData.toUShort(&conversionResult);
        if(!conversionResult)
        {
          throw conversion_error(strData,QObject::tr("not a valid uint16(unsigned 16 bit integer)") );
        }
        data.ui16 = rawValue;
      }
      break;
    case UINT_32:
      {
        ulong rawValue = strData.toULong(&conversionResult);
        if(!conversionResult)
        {
          throw conversion_error(strData,QObject::tr("not a valid uint32(unsigned 32 bit integer)") );
        }
        data.ui32 = rawValue;
      }
      break;
    case UINT_64:
      {
        qulonglong rawValue = strData.toULongLong(&conversionResult);
        if(!conversionResult)
        {
          throw conversion_error(strData,QObject::tr("not a valid uint64(unsigned 64 bit integer)") );
        }
        data.ui64 = rawValue;
      }
      break;
    case FLOAT_32:
      {
        float rawValue = strData.toFloat(&conversionResult);
        if(!conversionResult)
        {
          throw conversion_error(strData,QObject::tr("not a valid f32(32 bit float point)") );
        }
        data.f32 = rawValue;
      }
      break;
    case FLOAT_64:
      {
        float rawValue = strData.toDouble(&conversionResult);
        if(!conversionResult)
        {
          throw conversion_error(strData,QObject::tr("not a valid f64(64 bit float point)") );
        }
        data.f64 = rawValue;
      }
      break;
    case ARRAY:
      throw conversion_error(strData,QObject::tr("ARRAY not implimented"));
      break;
    case STRUCT:
      throw conversion_error(strData,QObject::tr("STRUCT not implimented"));
      break;
    case STRING:
      throw conversion_error(strData,QObject::tr("STRING not implimented"));
      break;
    case UNDEFINED:
      throw conversion_error(strData,QObject::tr("Can not convert UNDEFINED value to string"));
      break;
  }
}
blockDataVariable blockVariable::getVariable() const
{
  return this->data;
}

}
