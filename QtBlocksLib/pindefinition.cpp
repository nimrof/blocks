#include "exceptions.h"
#include "pindefinition.h"

namespace blocks
{

pinDefinition::pinDefinition(const QString name, const dataType type, const itemID index)
{
  this->name  = name;
  this->type  = type;
  this->index = index;
}
void pinDefinition::setName(QString name)
{
  this->name = name;
}
void pinDefinition::setDataType(dataType type)
{
  this->type = type;
}
itemID pinDefinition::getIndex() const
{
  return index;
}
QString pinDefinition::getName() const
{
  return name;
}
dataType pinDefinition::getDataType() const
{
  return type;
}
void pinDefinition::saveToXML(QDomElement &node, const int version) const
{
  (void)version;
  QDomElement pinNode = node.ownerDocument().createElement("pin");
  node.appendChild(pinNode);

  pinNode.setAttribute("type",blockVariable::datatypeToString(type));
  pinNode.setAttribute("name", name);
}
pinDefinition* pinDefinition::readFromXML(QDomElement node, const int version, const itemID index)
{
  (void)version;
  QString  name = node.attribute("name");
  dataType type = blockVariable::stringToDatatype( node.attribute("type") );

  return new pinDefinition(name,type,index);
}

}
