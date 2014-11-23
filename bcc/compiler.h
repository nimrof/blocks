#ifndef COMPILER_H
#define COMPILER_H

#include <QCoreApplication>
#include <QDataStream>
#include <blocks.h>

class compiler
{
public:
  compiler();
  virtual void configure(QCoreApplication& a) = 0;
  virtual bool compile(const blocks::project* pro) = 0;
protected:
  QDataStream programData;
  QDataStream debugData;
};




#endif // COMPILER_H
