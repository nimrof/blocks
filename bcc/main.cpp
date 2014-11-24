#include <QCoreApplication>
#include <QStringList>
#include <iostream>
#include <QVariant>

#include "main.h"
#include "project.h"

#include "simplecompiler.h"
#include "advancedcompiler.h"
#include "advancedthreadedcompiler.h"

int main(int argc, char *argv[])
{
  std::cerr << "internal error in file: " << __FILE__ << " at line: " << __LINE__ << std::endl;
  QCoreApplication a(argc, argv);

  prossesProgramArguments(a, a.arguments());

  QVariant inputProperty = a.property("input");

  if( inputProperty.isValid() && inputProperty.canConvert(QVariant::String) )
  {
    QString filePath = inputProperty.toString();
    blocks::project* project = loadAndValidateFile(filePath);
    if(project)
    {
      compiler* comp = getCompiler(a);
      comp->configure(a);
      comp->compile(project);
    }
  }
  else
  {
    std::cerr << "fatal error: no input file" << std::endl;
  }
  //return a.exec();
}
void prossesProgramArguments(QCoreApplication& a, const QStringList list)
{
  QStringList arguments;
  arguments << "output"<< "input" << "outputType" << "outputIndexSize" << "outputDebugfile" << "stripFileintegrityInfo";
  QStringList::const_iterator cItrList;
  for (cItrList = list.constBegin(); cItrList != list.constEnd(); ++cItrList)
  {
    QStringList::const_iterator cItrArg;
    for (cItrArg = arguments.constBegin(); cItrArg != arguments.constEnd(); ++cItrArg)
    {
      QString arg = "--" + *cItrArg + "=";
      if( cItrList->startsWith(arg))
      {
        QString value = *cItrList;
        value.replace(arg,QString());
        prossesParameter(a, *cItrArg,value);
      }
    }
  }
  validateProgramArguments(a);//validate the parameters and there values so that they are not in conflict with eatch other
}
void prossesParameter(QCoreApplication& a, const QString param, const QString value)
{
  if("output" == param)
  {
    //TODO: check for valid file/dir path
    a.setProperty(param.toLocal8Bit().data(),value);
  }
  else if("input" == param)
  {
    //TODO: check for valid file path
    a.setProperty(param.toLocal8Bit().data(),value);
  }
  else if("outputType" == param)
  {
    if (false == ("advancedThreaded" == value||
                  "advanced" == value ||
                  "simple" ==value) )
    {
      std::cerr << "value for:" + std::string( param.toLocal8Bit().constData() ) + " must be one of advancedThreaded|advanced|simple" << std::endl;
    }
    a.setProperty(param.toLocal8Bit().data(),value);
  }
  else if("outputIndexSize" == param)
  {
    bool wasInt;
    int indexSize = value.toInt(&wasInt);

    if(false == wasInt)
    {
      std::cerr << "value for:" + std::string( param.toLocal8Bit().constData() ) + " is not a interger value" << std::endl;
    }
    else if ( false == (8 == indexSize || 16 == indexSize || 32 == indexSize ) )
    {
      std::cerr << "value for:" + std::string( param.toLocal8Bit().constData() ) + " must be one of 8|16|32" << std::endl;
    }
    else
    {
      a.setProperty(param.toLocal8Bit().data(),indexSize);
    }
  }
  else if("outputDebugfile" == param)
  {
    //TODO: check for valid file/dir path
    a.setProperty(param.toLocal8Bit().data(),value);
  }
}
void validateProgramArguments(QCoreApplication& a)
{
  QVariant indexSize = a.property("outputIndexSize");

  if( !indexSize.isValid() )
  {
    qDebug("outputIndexSize defaulting to 32");

    a.setProperty("outputIndexSize",32);
  }
}
blocks::project* loadAndValidateFile(QString path)
{
  QString error;
  if( blocks::project::xsdValidateFile(path, error) == true)
  {
    blocks::project* pro = blocks::project::loadFile(path);
    return pro;
  }
  std::cerr << error.toLocal8Bit().data() << std::endl;
  return 0;
}
compiler* getCompiler(QCoreApplication& a)
{
  QVariant inputProperty = a.property("outputType");

  QString compilerType;

  if( inputProperty.isValid() && inputProperty.canConvert(QVariant::String) )
  {
    compilerType = inputProperty.toString();
  }
  else
  {
    qDebug("compilertype defaulting to advancedThreaded");
    compilerType = "advancedThreaded";
    compilerType = "simple";
  }

  if(compilerType == "simple")
  {
    return new simpleCompiler();
  }
  else if(compilerType == "advanced")
  {
    return new advancedCompiler();
  }
  else if(compilerType != "advancedThreaded")
  {
    return new advancedThreadedCompiler();
  }
  else
  {
    qDebug("Should not have gotten here: compiler* getCompiler()");
    return new advancedThreadedCompiler();
  }
}
