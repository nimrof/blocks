#include "BlocksMethode.h"
#include <iostream>
#include <string>
#include <fstream>
#include "BlocksScript.h"

BlocksMethode::BlocksMethode(void)
{
}

BlocksMethode::~BlocksMethode(void)
{
}

bool BlocksMethode::ReadFromXML(const TiXmlElement* MethodeNode )
{
  if ( MethodeNode->Attribute("id",&CallId) == NULL)
  {
    throw ("Methode Parce error [id] missing");
  }
  
  int NumInput;
  if ( MethodeNode->Attribute("input",&NumInput) == NULL)
  {
    throw ("Methode Parce error [input] missing");
  }

  int NumOutput;
  if ( MethodeNode->Attribute("output",&NumOutput) == NULL)
  {
    throw ("Methode Parce error [output] missing");
  }

  Input.resize(NumInput);
  Output.resize(NumOutput);
  OutputTypes.resize(Output.size());
  OutputBinding.resize(Output.size());

  const char* pMethode = MethodeNode->Attribute("methode");
  if ( pMethode == NULL)
  {
    throw ("Methode Parce error [methode] missing");
  }
  MethodeName = pMethode;

  const TiXmlNode* pOutputs = MethodeNode->FirstChild("outputs");
  if ( pOutputs == NULL)
  {
    throw ("Methode Parce error [outputs] missing");
  }

  for ( const TiXmlElement* pOutput = pOutputs->FirstChildElement( "output" ); pOutput != 0; pOutput = pOutput->NextSiblingElement( "output" ))
  {
    int OutputPin;
    int TargetBlock;
    int TargetPin;
    const char* pDataType = pOutput->Attribute("dataType");

    pOutput->Attribute("outputPin",  &OutputPin);	
    pOutput->Attribute("targetBlock",&TargetBlock);
    pOutput->Attribute("targetPin",  &TargetPin);

    std::cout << "Datatype=" << pDataType << " outputPin=" << OutputPin << " targetBlock=" << TargetBlock << " targetPin=" << TargetPin << std::endl;

    OutputBinding[OutputPin].push_back(std::make_pair(TargetBlock,TargetPin));

	if( OutputTypes[OutputPin].empty() == false )
    {
      //safetycheck that datatypes on the same outputpin does not differ
      if( OutputTypes[OutputPin] != pDataType )
      {
        std::cout << "Datatype in block:" << CallId << " on output pin:" << OutputPin << " have differen types on differten binding. Aborting";
        throw ("Methode Parce error [outputs] dataypes differ");
      }
    }
    else
    {
      OutputTypes[OutputPin] = pDataType;
    }
  }
  
  return true;
}

int BlocksMethode::GetMethodeID()
{
  return CallId;
}

void BlocksMethode::RegisterOutputVariables(BlocksScript* ParentScript)
{
  for(std::vector< std::string >::size_type i = 0; i < OutputTypes.size(); i++)
  {
    std::string DataType = OutputTypes[i];
	Output[i] = ParentScript->AddNewVariable(DataType);
  }
}

unsigned int BlocksMethode::GetNumInput()
{
	return Input.size();
}
unsigned int BlocksMethode::GetNumOutput()
{
	return Output.size();
}

std::vector<std::pair<unsigned int,unsigned int> > BlocksMethode::GetOutputBinding(unsigned int PinIndex)
{
  //Note: may throw out_of_range (included in <stdexcept> )
  return OutputBinding.at(PinIndex);
}

unsigned int BlocksMethode::GetOutputVariableIndex(const unsigned int OutputIndex)
{
  //Note: may throw out_of_range (included in <stdexcept> )
  return Output.at(OutputIndex);
}

void BlocksMethode::SetInputVariableIndex(const unsigned int InputIndex, const unsigned int Index)
{
  Input.at(InputIndex) = Index;
}

void BlocksMethode::WriteToFile(std::ofstream &File)
{
  unsigned int NameHash = jenkins_one_at_a_time_hash((unsigned char*)MethodeName.c_str(),MethodeName.size() );
  File.write((char*)&NameHash,sizeof(NameHash));

  unsigned int NumInput  = Input.size();
  unsigned int NumOutput = Output.size();

  File.write((char*)&NumInput, sizeof(NumInput));
  File.write((char*)&NumOutput,sizeof(NumOutput));

  for (unsigned int i = 0; i < NumInput; i++)
  {
    unsigned int VariabelIndex = Input.at(i);    
    File.write((char*)&VariabelIndex,sizeof(VariabelIndex));
  }

  for (unsigned int i = 0; i < NumOutput; i++)
  {
    unsigned int VariabelIndex = Output.at(i);    
    File.write((char*)&VariabelIndex,sizeof(VariabelIndex));
  }
}

const std::string BlocksMethode::GetName()
{
  return MethodeName;
}
