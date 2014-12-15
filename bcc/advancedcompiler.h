#ifndef ADVANCEDCOMPILER_H
#define ADVANCEDCOMPILER_H

#include "compiler.h"

class advancedCompiler : public compiler
{
public:
  advancedCompiler();
  virtual void configure(QCoreApplication& a);
  virtual bool DoCompile(const blocks::project* pro);
};

#endif // ADVANCEDCOMPILER_H
