#ifndef COMPILER_H
#define COMPILER_H

#include <QCoreApplication>
#include <QDataStream>
#include <blocks.h>

class compiler
{
public:
  compiler();
  virtual void configure(QCoreApplication& a);
  bool compile(const blocks::project* pro);
  virtual bool DoCompile(const blocks::project* pro) = 0;
protected:
  QDataStream programData;
  QDataStream debugData;
  QString outFilePath;

};

#endif // COMPILER_H
