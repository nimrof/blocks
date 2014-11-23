#ifndef CONNECTION_SIMULATOR_H
#define CONNECTION_SIMULATOR_H

#include <QObject>
#include <QtPlugin>
#include <QDebug>

#include "../QtBlocksLib/interface/deviceconnection.h"

class Connection_Simulator : public QObject, DeviceConnection
{
  Q_OBJECT
  Q_INTERFACES(DeviceConnection)
public:
  Connection_Simulator();
  virtual QString getShortName();
};


#endif // CONNECTION_SIMULATOR_H


