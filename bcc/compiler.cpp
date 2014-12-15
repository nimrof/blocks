#include "compiler.h"
#include <QVariant>
#include <QFile>

compiler::compiler()
{
}

void compiler::configure(QCoreApplication& a)
{
  outFilePath = a.property("output").toString();
}

bool compiler::compile(const blocks::project* pro)
{
  QFile* file = new QFile(outFilePath);

  file->open(QIODevice::WriteOnly);
  programData.setDevice(file);
  //5= QDataStream(&file);
  QDataStream debugData;

  bool result = DoCompile(pro);

  file->close();
  return result;
}
