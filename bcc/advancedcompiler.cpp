#include "advancedcompiler.h"

advancedCompiler::advancedCompiler()
{
}

void advancedCompiler::configure(QCoreApplication& a){Q_UNUSED(a)}
bool advancedCompiler::DoCompile(const blocks::project* pro){Q_UNUSED(pro);return true;}
