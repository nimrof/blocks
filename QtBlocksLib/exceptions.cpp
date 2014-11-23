#include <QObject>
#include "exceptions.h"

namespace blocks
{

QStringExceptions::QStringExceptions()
{
  why = "Undefined";
}
const QString QStringExceptions::what() const
{
  return why;
}
xml_parse_exception::xml_parse_exception(const QString why, const QString parentException)
{
  this->why = why;
  this->parentWhy = parentException;
}
xml_logic_error::xml_logic_error(const QString why, const QString parentException)
{
  this->why = why;
  this->parentWhy = parentException;
}
conversion_error::conversion_error(const QString valueString, const QString why, const QString parentException)
{
  this->why = QString(QObject::tr("Convertion of %1 failed: %2")).arg(valueString).arg(why);
  this->parentWhy = parentException;
}
unknownBlockID_error::unknownBlockID_error(const int blockID, const QString extraInfo, const QString parentException)
{
  this->why = QString(QObject::tr("Trying to find a block with ID: %1 failed. %2")).arg(blockID).arg(extraInfo);
  this->parentWhy = parentException;
}
blockIDNotFree_error::blockIDNotFree_error(const int blockID, const QString extraInfo, const QString parentException)
{
  this->why = QString(QObject::tr("Trying to create a block with ID: %1 failed. %2")).arg(blockID).arg(extraInfo);
  this->parentWhy = parentException;
}
unknownPinIndex_error::unknownPinIndex_error(const int pinIndex, const QString extraInfo, const QString parentException)
{
  this->why = QString(QObject::tr("Failed to find to the pin with index: %1 failed. %2")).arg(pinIndex).arg(extraInfo);
  this->parentWhy = parentException;
}

}
