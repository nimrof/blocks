#include <stdexcept>

#include <QStringList>
#include <QFile>
#include <QDomDocument>
#include <QXmlSchema>
#include <QXmlSchemaValidator>
#include <QAbstractMessageHandler>

#include "exceptions.h"
#include "project.h"
#include "script.h"

class MessageHandler : public QAbstractMessageHandler
{
public:
MessageHandler() : QAbstractMessageHandler(0)
{
}

QString statusMessage() const
{
  return m_description;
}

int line() const
{
  return m_sourceLocation.line();
}

int column() const
{
  return m_sourceLocation.column();
}

protected:
virtual void handleMessage(QtMsgType type, const QString &description, const QUrl &identifier, const QSourceLocation &sourceLocation)
{
  Q_UNUSED(type);
  Q_UNUSED(identifier);

  m_messageType = type;
  m_description = description;
  m_sourceLocation = sourceLocation;
}

private:
  QtMsgType m_messageType;
  QString m_description;
  QSourceLocation m_sourceLocation;
};

namespace blocks
{
project::project()
{
  name = "vvv";
}
callDefinition* project::getcallDefinition(QString fullName) const
{
  const library* lib;
  QString definitionName;

  QStringList separatedName = fullName.split("::", QString::SkipEmptyParts);
  if(separatedName.size() == 1)
  {
    //project internal blocks
    definitionName = separatedName.at(0);
    lib = projectLibrary;
  }
  else
  {
    QString libraryName = separatedName.at(0);

    std::map<QString, library*>::const_iterator cit;

    cit = externalLibrary.find(libraryName);

    if(cit != externalLibrary.end() )
    {
      separatedName.removeFirst();
      definitionName = separatedName.join("::");
      lib = cit->second;
    }
    else
    {
      lib = NULL;
    }
  }

  if(lib == NULL)
  {
    return NULL;
  }
  else
  {
    return lib->getcallDefinition(definitionName);
  }
}
project* project::loadFile(QString path)
{
  QDomDocument domDocument;
  QFile file(path);

  if (!file.open(QFile::ReadOnly | QFile::Text))
  {
    throw std::invalid_argument("failed to open file");
  }
  QString errorStr;
  int errorLine;
  int errorColumn;

  if (!domDocument.setContent(&file, true, &errorStr, &errorLine, &errorColumn))
  {
    //TODO: WRONG exception
//    throw std::invalid_argument(errorStr);
  }

  QDomElement root = domDocument.documentElement();

  try
  {
    return readFromXML(root);
  }
  catch (QStringExceptions e)
  {
//    QString error =
    return NULL;
  }
}
void project::saveFile(const QString path, const int version)
{
  QFile file(path);

  if (!file.open(QFile::WriteOnly | QFile::Text))
  {
    throw std::invalid_argument("failed to open file");
  }

  QDomDocument domDocument;
  QDomElement root = domDocument.createElement("blocks");
  domDocument.appendChild(root);

  try
  {
    saveToXML(root,version);
    QByteArray tes = domDocument.toByteArray();
    file.write(tes);
  }
  catch (QStringExceptions e)
  {
//    QString error =
    return;
  }
}
bool project::xsdValidateFile(const QString path, QString &error)
{
  QString xsdpath = "../../../blocksProject.xsd";
  QFile schemaFile(xsdpath);
  schemaFile.open(QFile::ReadOnly | QFile::Text);

  if(schemaFile.error() != QFile::NoError)
  {
    error = "Failed to load schemafile";
    return false;
  }
  QXmlSchema schema;
  MessageHandler msghdl;
  QByteArray gg = schemaFile.readAll();
  schema.load(gg);
//  schema.setMessageHandler(&msghdl);

  if (schema.isValid())
  {
    QFile file(path);
    file.open(QIODevice::ReadOnly);

    QXmlSchemaValidator validator(schema);
    if (validator.validate(&file, QUrl::fromLocalFile(file.fileName())))
    {
      error = "instance document is valid";
      return true;
    }
    else
    {
      error = "instance document is invalid";
      return false;
    }
  }
  return false;
}
project* project::readFromXML(const QDomElement node)
{
  int fileVersion;

  bool versionReadOK;
  fileVersion = node.attribute("version").toFloat(&versionReadOK) * 100;

  if(!versionReadOK)
  {
    throw xml_parse_exception(QObject::tr("version attribute not float"));
  }

  project* proj = new project();
  QDomElement child = node.firstChildElement("blocks");
  if ( !child.isNull() )
  {
    proj->projectLibrary = library::readFromXML(child,fileVersion);
  }

  child = node.firstChildElement("script");
  while (!child.isNull())
  {
    script* s = new script(proj);
    s->readFromXML(child,fileVersion, *proj );
    child = child.nextSiblingElement("script");
    proj->scriptList.insert(std::make_pair(s->getName(),s));
  }
  return proj;
}
void project::saveToXML(QDomElement& node, const int version)
{
  node.setAttribute("version", ((float)version / 100.0) );

  {
    QDomElement projLibNode = node.ownerDocument().createElement("blocks");
    node.appendChild(projLibNode);
    projectLibrary->saveToXML(projLibNode,version);
  }

  std::map<QString, script*>::iterator it;
  for ( it = scriptList.begin(); it != scriptList.end(); it++ )
  {
    QDomElement scriptNode = node.ownerDocument().createElement("script");
    node.appendChild(scriptNode);
    it->second->saveToXML(scriptNode,version);
  }
}
QString  project::getName() const
{
  return name;
}
library* project::getProjectLibrary()
{
  return projectLibrary;
}
QStringList project::getLibraryList() const
{
  QStringList list;

  for(std::map<QString, library*>::const_iterator i = externalLibrary.begin(); i != externalLibrary.end(); ++i )
  {
    list << i->second->getName();
  }
  return list;
}
library* project::getLibrary(const QString libName) const
{
  std::map<QString, library*>::const_iterator it;

  it = externalLibrary.find(libName);

  if( it == externalLibrary.end() )
  {
    return NULL;
  }
  else
  {
    return it->second;
  }
}
QStringList project::getScriptList() const
{
  QStringList list;

  for(std::map<QString, script*>::const_iterator i = scriptList.begin(); i != scriptList.end(); ++i )
  {
    list << i->second->getName();
  }
  return list;
}
script* project::getScript(const QString scriptName) const
{
  std::map<QString, script*>::const_iterator it;
  it = scriptList.find(scriptName);

  if( it == scriptList.end() )
  {
    return NULL;
  }
  else
  {
    return it->second;
  }
}

}
