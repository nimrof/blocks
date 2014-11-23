#include "connection_simulator.h"

#include <QString>

int main()
{
  return 0;
}

Connection_Simulator::Connection_Simulator()
{
}

Q_EXPORT_PLUGIN2( Connection_Simulator, Connection_Simulator )

QString Connection_Simulator::getShortName()
{
  return QString("Simulator plug-in");
}
