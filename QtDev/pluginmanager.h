#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H


#include <QObject>
#include <QDebug>
#include <QDir>
#include <QString>
#include <QPluginLoader>
#include "interface/deviceconnection.h"

class pluginManager : public QObject
{
  Q_OBJECT
public:
  pluginManager(QObject *parent = 0);
  void LoadAllPlugins();
  void LoadPlugin(QString Filename);
};

#endif // PLUGINMANAGER_H
