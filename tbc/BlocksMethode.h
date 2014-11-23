#pragma once
#include <map>
#include <vector>
#include <string>
#include "../lib/tinyxml2/tinyxml.h"

class BlocksScript;

class BlocksMethode
{
public:
  BlocksMethode(void);
  ~BlocksMethode(void);
  bool ReadFromXML(const TiXmlElement* ScriptNode );
  void RegisterOutputVariables(BlocksScript* ParentScript);
  int GetMethodeID();
  const std::string GetName();
  unsigned int GetNumInput();
  unsigned int GetNumOutput();
  unsigned int GetOutputVariableIndex(const unsigned int OutputIndex);
  unsigned int GetOutputVariableIndex();
  void SetInputVariableIndex(const unsigned int InputIndex, const unsigned int Index);
  std::vector<std::pair<unsigned int,unsigned int> > GetOutputBinding(unsigned int PinIndex);
  void WriteToFile(std::ofstream &File);
private:
  int CallId;
  std::string MethodeName;
  std::vector<unsigned int> Input;
  std::vector<unsigned int> Output;

  std::vector< std::vector<std::pair<unsigned int,unsigned int> > > OutputBinding;
  std::vector<std::string> OutputTypes;
};
