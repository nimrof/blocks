#pragma once
#include "../lib/tinyxml2/tinyxml.h"
#include <map>
#include <vector>
#include <string>
#include "BlocksMethode.h"

class BlocksScript
{
public:
  BlocksScript(void);
  ~BlocksScript(void);
  bool ReadFromXML(const TiXmlNode* ScriptNode );
  void RegisterOutputVariables();
  unsigned int AddNewVariable(std::string);
  void BindInputToOutput();
  void WriteToFile(std::ofstream &File);
private:
  std::map<unsigned int, BlocksMethode> MethodeList;
  std::vector<std::string> VariableList;
};

unsigned int jenkins_one_at_a_time_hash(const unsigned char* key, unsigned int key_len);
