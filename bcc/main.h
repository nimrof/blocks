#ifndef MAIN_H
#define MAIN_H

#include <QString>
#include <blocks.h>
#include "compiler.h"
#include <QCoreApplication>

void prossesParameter(QCoreApplication& a, const QString param, const QString value);
void prossesProgramArguments(QCoreApplication& a, const QStringList list);
void validateProgramArguments(QCoreApplication& a);
blocks::project *loadAndValidateFile(QString path);
compiler* getCompiler(QCoreApplication& a);

#endif // MAIN_H
