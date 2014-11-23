#ifndef LIBRARY_H
#define LIBRARY_H

#include <map>

#include <QString>
#include <QObject>
#include <QDomDocument>

#include "blocks.h"

namespace blocks
{

class library
{
//  Q_OBJECT
public:
  library                              (QString name = "internal");
  QString         getName              ()                                           const;
  void            saveToXML            (QDomElement &node, const int version);
  static library* readFromXML          (const QDomElement node, const int version);
  void            addcallDefinition    (callDefinition *blockDef);
  QStringList     getcallDefinitionList()                                           const;
  callDefinition* getcallDefinition    (const QString name)                         const;
  void            removecallDefinition (const QString defName);
private:
  std::map<QString, callDefinition*> definitions;
  QString name;
};

}

#endif // LIBRARY_H
