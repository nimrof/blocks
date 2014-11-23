#ifndef BLOCKVARIABLE_H
#define BLOCKVARIABLE_H

#include <QString>

namespace blocks
{

enum dataType
{
  UNDEFINED =  0,//datatype is not defined
  RUN       =  1,//green
  BOOLEAN   =  2,//green
  INT_8     =  3,//blue
  INT_16    =  4,
  INT_32    =  5,
  INT_64    =  6,
  UINT_8    =  7,
  UINT_16   =  8,
  UINT_32   =  9,
  UINT_64   = 10,
  FLOAT_32  = 11,//orange
  FLOAT_64  = 12,
  ARRAY     = 13,//base color
  STRUCT    = 14,
  STRING    = 15//pink
};

union blockDataVariable//TODO: replace this with
{
  bool        b;
  qint8      i8;
  qint16    i16;
  qint32    i32;
  qint64    i64;
  quint8    ui8;
  quint16  ui16;
  quint32  ui32;
  quint64  ui64;
  float     f32;
  double    f64;
};

class blockVariable
{
public:
  blockVariable                   (void           );
  blockVariable                   (const QString type,     const QString value);
  blockVariable                   (const dataType varType, const QString strData);
  blockVariable                   (const bool    b);
  blockVariable                   (const qint8   i);
  blockVariable                   (const qint16  i);
  blockVariable                   (const qint32  i);
  blockVariable                   (const qint64  i);
  blockVariable                   (const quint8  i);
  blockVariable                   (const quint16 i);
  blockVariable                   (const quint32 i);
  blockVariable                   (const quint64 i);
  blockVariable                   (const float   f);
  blockVariable                   (const double  f);

  dataType          getDataType     () const;
  void              changeDatatype  (const dataType newDatatype);
  QString           dataToString    () const;
  void              stringToData    (const QString strData);
  blockDataVariable getVariable     () const;

  static dataType   stringToDatatype(const QString str);
  static QString    datatypeToString(const dataType type);
private:
  dataType          type;
  blockDataVariable data;
};

}
#endif // BLOCKVARIABLE_H
