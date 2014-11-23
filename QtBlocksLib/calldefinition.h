#ifndef CALLDEFINITION_H
#define CALLDEFINITION_H

#include <vector>

#include <QDomDocument>
#include <QString>

#include "blocks.h"
#include "pindefinition.h"

namespace blocks
{

class callDefinition : public QObject
{
  Q_OBJECT
public:
  callDefinition                          (library* parent);
  void                    setLibrary      (library* parent);
  library*                getLibrary      ();
  void                    setName         (QString newName);
  QString                 getName         (void)                                      const;
  QString                 getFullName     (void)                                      const;
  void                    addPin          (const pinType pt, pinDefinition *newPin);
  bool                    removePin       (const pinType pt, itemID index);
  itemID getNumPinsOfType(const pinType pt)                          const;
  pinDefinition*          getPin          (const pinType pt, itemID index) const;
  void                    saveToXML       (QDomElement &node, const int version)       const;
  static callDefinition*  readFromXML     (const QDomElement node, const int version);
private:
  QString                     name;
  std::vector<pinDefinition*> pinIn;
  std::vector<pinDefinition*> pinOut;
  library*                    parentLibrary;
};

}

#endif // CALLDEFINITION_H
