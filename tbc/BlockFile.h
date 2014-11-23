#pragma once
#include "BlocksScript.h"
#include <vector>
#include <utility>

class BlockFile
{
public:
  BlockFile(void);
  ~BlockFile(void);
  void LoadFile(const std::string FilePath);
  void RegisterOutputVariables();
  void BindInputToOutput();
  void WriteToFile(const std::string);
private:
  std::vector < std::pair<std::string,BlocksScript> > scripts;
};