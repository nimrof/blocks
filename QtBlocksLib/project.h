#ifndef PROJECT_H
#define PROJECT_H

#include <map>

#include <QString>

#include "library.h"

#include "blocks.h"

namespace blocks
{

class project : public QObject
{
  Q_OBJECT
public:
  project();
  void            saveToXML         (QDomDocument XMLDoc, QDomElement node) const;
  callDefinition* getcallDefinition (QString fullName)                      const;
  static project* loadFile          (const QString path);
  void            saveFile          (const QString path, const int version);

  static bool     xsdValidateFile   (const QString path, QString &error);
  static project* readFromXML       (const QDomElement node);
  void            saveToXML         (QDomElement &node, const int version);

  QString         getName           ()                                      const;
  library*        getProjectLibrary ();
  QStringList     getLibraryList    ()                                      const;
  library*        getLibrary        (const QString libName)                 const;
  QStringList     getScriptList     ()                                      const;
  script*         getScript         (const QString scriptName)              const;
private:
  QString                     name;
  QString                     location;//as in location on disk

  library*                    projectLibrary;
  std::map<QString, library*> externalLibrary;
  std::map<QString, script*>  scriptList;
};

}
#endif // PROJECT_H
