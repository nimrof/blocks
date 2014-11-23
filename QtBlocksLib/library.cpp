#include <QStringList>

#include "library.h"
#include "calldefinition.h"

namespace blocks
{

library::library(QString name)
{
  this->name = name;
}
QString library::getName() const
{
  return name;
}
void library::saveToXML(QDomElement &node, const int version)
{
  std::map<QString, callDefinition*>::iterator it;
  for ( it = definitions.begin(); it != definitions.end(); it++ )
  {
    QDomElement blockNode = node.ownerDocument().createElement("block");
    node.appendChild(blockNode);

    callDefinition* callDef = it->second;
    blockNode.setAttribute("name", callDef->getName() );
    callDef->saveToXML(blockNode,version);
  }
}
library* library::readFromXML(const QDomElement node, const int version)
{
  library* lib = new library(QString());

  if(node.tagName() != "blocks")
  {
    throw "internal error: node with tagname != blocks was sendt to library parser";
  }

  QDomElement child = node.firstChildElement("block");
  while (!child.isNull())
  {
    callDefinition* blockDef = callDefinition::readFromXML(child, version);
    lib->addcallDefinition(blockDef);
    child = child.nextSiblingElement("block");
  }
  return lib;
}
void library::addcallDefinition(callDefinition* blockDef)
{
  blockDef->setLibrary(this);
  definitions.insert( std::make_pair(blockDef->getName(),blockDef) );
}
QStringList library::getcallDefinitionList() const
{
  QStringList list;

  for(std::map<QString, callDefinition*>::const_iterator i = definitions.begin(); i != definitions.end(); ++i )
  {
    list << i->first;
  }
  return list;
}
void library::removecallDefinition(const QString defName)
{
  std::map<QString, callDefinition*>::iterator it;
  it = definitions.find(defName);
  definitions.erase(it);
}
callDefinition* library::getcallDefinition(const QString name) const
{
  std::map<QString, callDefinition*>::const_iterator it;

  it = definitions.find(name);

  if( it == definitions.end() )
  {
    return NULL;
  }
  else
  {
    return it->second;
  }
}

}
