#include "BlockFile.h"
#include "BlocksScript.h"
#include <iostream>
#include <fstream>

BlockFile::BlockFile(void)
{
}

BlockFile::~BlockFile(void)
{
}

void BlockFile::LoadFile(const std::string FilePath)
{
  TiXmlDocument doc(FilePath.c_str());
  bool loadOkay = doc.LoadFile();
  if (loadOkay)
  {
    const TiXmlElement* RootNode = doc.RootElement();

    if( strcmp(RootNode->Value(),"Blocks") != 0 )
    {
      std::cout << "The input file is not a Block designer file (missing Blocks root node)" << std::endl;			
    }
    else
    {
      for (const TiXmlElement* pScript = RootNode->FirstChildElement( "script" ); pScript != 0; pScript = RootNode->NextSiblingElement( "script" ))
      {
        BlocksScript script;
        script.ReadFromXML(pScript);
		scripts.push_back( std::make_pair("Name",script) );
      }
    }
  }
  else
  {
    std::cout << "Failed to load" << "InputFile" << std::endl;
  }
}
void BlockFile::RegisterOutputVariables()
{
  for( std::vector< std::pair<std::string,BlocksScript> >::iterator Script = scripts.begin(); Script != scripts.end(); Script++ )
  {
    Script->second.RegisterOutputVariables();
  }
}
void BlockFile::BindInputToOutput()
{
  for( std::vector< std::pair<std::string,BlocksScript> >::iterator Script = scripts.begin(); Script != scripts.end(); Script++ )
  {
    Script->second.BindInputToOutput();
  }
}
void BlockFile::WriteToFile(const std::string FilePath)
{
  std::ofstream File(FilePath.c_str(), std::ios::in | std::ios::binary);
  std::string PreFix = "BCCF";
  File.write(PreFix.c_str(),PreFix.size());
  unsigned int NumScript = scripts.size();

  File.write((char*)&NumScript,sizeof(NumScript));
  for( std::vector< std::pair<std::string,BlocksScript> >::iterator Script = scripts.begin(); Script != scripts.end(); Script++ )
  {
    Script->second.WriteToFile(File);
  }
}