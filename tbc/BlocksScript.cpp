#include "BlocksScript.h"
#include <iostream>
#include <fstream>

BlocksScript::BlocksScript(void)
{
}
BlocksScript::~BlocksScript(void)
{
}
void BlocksScript::RegisterOutputVariables()
{
  for( std::map<unsigned int, BlocksMethode>::iterator i = MethodeList.begin(); i != MethodeList.end(); i++ )
  {
	  i->second.RegisterOutputVariables(this);
  }
}
unsigned int jenkins_one_at_a_time_hash(const unsigned char* key, unsigned int key_len)
{
    unsigned int hash = 0;
    unsigned int i;
 
    for (i = 0; i < key_len; i++)
	{
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

bool BlocksScript::ReadFromXML( const TiXmlNode* ScriptNode )
{
  const TiXmlNode* ConnectionsNode = ScriptNode->FirstChild("connections");
  if( ConnectionsNode == NULL ) 
  {
    std::cout << "Failed to find connections node in script node" << std::endl;
    return false;
  }
  else
  {
    for ( const TiXmlElement* pBlock = ConnectionsNode->FirstChildElement( "block" ); pBlock != 0; pBlock = pBlock->NextSiblingElement( "block" ))
    {
      BlocksMethode NewMethode;
	  NewMethode.ReadFromXML(pBlock);
	  MethodeList[ NewMethode.GetMethodeID() ] = NewMethode;
    }
    return true;
  }
}

unsigned int BlocksScript::AddNewVariable(std::string Datatype)
{
  unsigned int VariableID = VariableList.size();
  VariableList.push_back( Datatype );
  return VariableID;
}

void BlocksScript::BindInputToOutput()
{
  for( std::map<unsigned int, BlocksMethode>::iterator methode = MethodeList.begin(); methode != MethodeList.end(); methode++ )
  {
    unsigned int NumOutput = methode->second.GetNumOutput();
    for (unsigned int i = 0; i < NumOutput; i++)
    {
      std::vector<std::pair<unsigned int,unsigned int> > PinOutBinding;
	  PinOutBinding = methode->second.GetOutputBinding(i);
	  for( std::vector<std::pair<unsigned int,unsigned int> >::iterator Binding = PinOutBinding.begin(); Binding != PinOutBinding.end(); Binding++ )
      {
        unsigned int VariableIndex = methode->second.GetOutputVariableIndex(i);
        unsigned int TargetBlock   = Binding->first;
        unsigned int TargetPin     = Binding->second;
        
		MethodeList[TargetBlock].SetInputVariableIndex(TargetPin,VariableIndex);
      }
    }
  }
}

void BlocksScript::WriteToFile(std::ofstream &File)
{
  //Print the variablelist
  unsigned int NumVariable = VariableList.size();
  File.write((char*)&NumVariable,sizeof(NumVariable));
  
  for( std::vector<std::string>::iterator i = VariableList.begin(); i != VariableList.end(); i++ )
  {
	unsigned int TypeHash = jenkins_one_at_a_time_hash((unsigned char*)i->c_str(),i->size() );
    File.write((char*)&TypeHash,sizeof(TypeHash));
  }
  
  unsigned int NumMethode = MethodeList.size();
  File.write((char*)&NumMethode,sizeof(NumMethode));
  for( std::map<unsigned int, BlocksMethode>::iterator methode = MethodeList.begin(); methode != MethodeList.end(); methode++ )
  {
	  methode->second.WriteToFile(File);
  }
}
