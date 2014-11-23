#include "pluginmanager.h"

pluginManager::pluginManager(QObject *parent) : QObject(parent)
{
}

void pluginManager::LoadAllPlugins()
{
  QDir path(QDir::currentPath() + "/plugins");

  //try to load the plugins
  foreach( QString filename, path.entryList(QDir::Files))
  {
    LoadPlugin(path.absolutePath() + "/" +  filename);
  }
}

void pluginManager::LoadPlugin(QString Filename)
{
  QPluginLoader loader(Filename);
  QObject *possiblePlugin = loader.instance();

  if(possiblePlugin)
  {
    DeviceConnection *plugin = qobject_cast<DeviceConnection*>( possiblePlugin );
    if( plugin )
    {
      qDebug() << "Loaded: " << plugin->getShortName();
    }
  }
  else
  {
    qDebug() << "Not a plugin: " << Filename << " = " << loader.errorString();
  }
}
