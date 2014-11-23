#include <QtWidgets/QApplication>
#include "mainwindow.h"

#include "pluginmanager.h"

int main(int argc, char *argv[])
{

  QApplication a(argc, argv);
  MainWindow w;

  pluginManager man;
  man.LoadAllPlugins();

  w.show();

  return a.exec();
}
