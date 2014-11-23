#ifndef PINDEF_H
#define PINDEF_H

#include <QString>
#include <QDomElement>
#include <QObject>

#include "blockvariable.h"
#include "blocks.h"

namespace blocks
{

enum pinType
{
  input,
  output
};

class pinDefinition : public QObject
{
  Q_OBJECT
public:
  pinDefinition                    (const QString name, const dataType type, const itemID index);
  void                  setName    (QString name);
  void                  setDataType(dataType type);
  itemID                getIndex   ()                                          const;
  QString               getName    ()                                          const;
  dataType              getDataType()                                          const;
  void                  saveToXML  (QDomElement &node, const  int version)      const;
  static pinDefinition* readFromXML(const QDomElement node, const int version, const itemID index);
private:
  QString  name;
  dataType type;
  itemID   index;
};

}


#endif // PINDEF_H
