#include "tbVM.h"
#include "tbLoader.h"

#include "main.h"
#include <stdio.h>

int main( int argc, char *argv[], char *envp[] )
{
  char* InputFile;
  struct tbVM* MyVM = CreateVM();

  argc;
  argv;
  envp;

  InputFile = argv[1];

  tbRegisterFunction(MyVM, &ReadAnalogIn,   "Read Analog in");
  tbRegisterFunction(MyVM, &AddInt,         "Add int");
  tbRegisterFunction(MyVM, &WriteAnalogOut, "Write Analog out");

  tbLoadFile(MyVM, InputFile );
  tbRunVMOneIteration(MyVM);
  return 0;
}

int ReadAnalogIn(struct Parameter** Input, int NumInput, struct Parameter** Output, int NumOutput)
{
  Input;
  NumInput;
  Output;
  NumOutput;
  printf("Running: ReadAnalogIn\n");

  if(tbSetIntegerOutput(Output, NumOutput, 0, 123) == TB_ERROR)
  {
	printf("hmmmmm... error in ReadAnalogIn\n");    
  }

  return 0;
}
int AddInt(struct Parameter** Input, int NumInput, struct Parameter** Output, int NumOutput)
{
  int Tall1;
  int Tall2;

  if(tbGetIntegerInput(Input, NumInput, 0, &Tall1) == TB_ERROR)
  {
	printf("hmmmmm... error in AddInt\n");
  }

  if(tbGetIntegerInput(Input, NumInput, 1, &Tall2) == TB_ERROR)
  {
	printf("hmmmmm... error in AddInt\n");
  }

  if(tbSetIntegerOutput(Output, NumOutput, 0, Tall1 + Tall2) == TB_ERROR)
  {
	printf("hmmmmm... error in AddInt\n");
  }

  NumInput;
  NumOutput;
  printf("Running: AddInt\n");
  return 0;
}
int WriteAnalogOut(struct Parameter** Input, int NumInput, struct Parameter** Output, int NumOutput)
{
  Input;
  NumInput;
  Output;
  NumOutput;
  printf("Running: WriteAnalogOut\n");
  return 0;
}
