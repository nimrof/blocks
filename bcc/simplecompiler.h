#ifndef SIMPLECOMPILER_H
#define SIMPLECOMPILER_H

#include "compiler.h"
#include <QString>
#include <vector>

class simpleCompiler : public compiler
{
public:
  simpleCompiler();
  virtual void configure(QCoreApplication& a);
  virtual bool compile(const blocks::project* pro);
  bool compileScript(const blocks::script &s, QDataStream &ps, QDataStream &ds);
  bool generateCalllist(const blocks::script* s, std::vector <blocks::itemID> &callList);
private:
  int     bitSize;
  QString outputPath;
  bool    makeDebugfile;
  QString debugOutputPath;
};

#endif // SIMPLECOMPILER_H
