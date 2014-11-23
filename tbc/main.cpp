#include "../lib/tinyxml2/tinyxml.h"
#include "BlockFile.h"
#include <iostream>

int main( int argc, char *argv[], char *envp[] )
{
  envp;
  argc;

  char* Option     = 0;
  char* InputFile  = 0;
  char* OutputFile = 0;

  if( argc < 3 )
  {
    std::cout << "tbc: some/all parameter missing :(" << std::endl;
    std::cout << "  tbc [-v -b{1-4}] inputfile outputfile" << std::endl;
    std::cout << "  -v verbos compiling" << std::endl;
    std::cout << "  -b{1/2/4}] index value byte size" << std::endl;
    return 0;
  }
  InputFile  = argv[argc-2];
  OutputFile = argv[argc-1];


  if ( argc == 4 )
  {
    Option     = argv[1];
  }

  std::cout << argc << std::endl;
  std::cout << "Inputfile: " << InputFile << std::endl;
  std::cout << "Output: " << OutputFile << std::endl;

  BlockFile File;
  File.LoadFile( InputFile );
  File.RegisterOutputVariables();
  File.BindInputToOutput();
  File.WriteToFile( OutputFile );
}
