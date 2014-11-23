#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <QString>

namespace blocks
{

class QStringExceptions
{
public:
  QStringExceptions();
//  virtual ~QStringExceptions();
  const QString what() const;
protected:
  QString why;
  QString parentWhy;
};

class xml_parse_exception : public QStringExceptions
{
public:
  xml_parse_exception(const QString why, const QString parentException = QString());
//  virtual ~xml_parse_exception();
};

class xml_logic_error : public QStringExceptions
{
public:
  xml_logic_error(const QString why, const QString parentException = QString());
//  virtual ~xml_logic_error();
};

class conversion_error: public QStringExceptions
{
public:
  conversion_error(const QString valueString, const QString why, const QString parentException = QString());
//  virtual ~xml_logic_error();
};

class unknownBlockID_error: public QStringExceptions
{
public:
  unknownBlockID_error(const int blockID, const QString extraInfo, const QString parentException = QString());
};

class blockIDNotFree_error: public QStringExceptions
{
public:
  blockIDNotFree_error(const int blockID, const QString extraInfo, const QString parentException = QString());
};

class unknownPinIndex_error: public QStringExceptions
{
public:
  unknownPinIndex_error(const int blockID, const QString extraInfo, const QString parentException = QString());
};

}

#endif // EXCEPTIONS_H
