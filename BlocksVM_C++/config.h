
//uses a extra byte pr. variable to save variable type, faster but uses more memory
#define BLOCKS_USE_TYPE_VARIABLE

//Will uses the same memory space for multiple variables if compiled file wants it, needs BLOCKS_USE_TYPE_VARIABLE to be defined
#define BLOCKS_USE_VARIABLE_RECYCLING

//Will tread operator blocks as normal blocks, uses less ram (1xBLOCKS_INTEGER_SIZE pr function), but may be slower as it need to run blocks all blocks all the time
#define BLOCKS_TREAT_OPERATOR_AS_NORMAL

//The integer size, the datasize the cpu works best with, should be 8 if using a 8-bit cpu and 16 on a 16-bit cpu..etc
#define BLOCKS_INTEGER_SIZE 8

//The size of the function name hash, value (8,16 or 32)
#define BLOCKS_HASH_SIZE 16

//The size of the integer that holds the ID for variables. Should be as small as possible to save ram, but maybe better to set to 32 on 32-bit cpu
#define BLOCKS_VARIABLE_INDEX_SIZE 8

//Enable blocks debug messages
#define BLOCKS_DEBUG_MSG 1

//Debug level to use
//3< Info           : status messages, function called ok, script loaded ok etc.
//2  Warning        : Indication that something might be wrong
//1  Error          : Non VM critical errors, function returned error, result may be totaly wrong but VM can go on.
//0 Critical Error  : Critical errors, vm will shutdown after one of these, canary, out of memory etc.
#define BLOCKS_CONSOLE_DEBUG_LEVEL 4

//Compiler-time checks
#if defined(BLOCKS_USE_VARIABLE_RECYCLING) && !defined(BLOCKS_USE_TYPE_VARIABLE)
  #error "BLOCKS_USE_VARIABLE_RECYCLING need BLOCKS_USE_TYPE_VARIABLE to be defined (see config.h)"
#endif

#if (BLOCKS_INTEGER_SIZE != 8) && (BLOCKS_INTEGER_SIZE != 16) && (BLOCKS_INTEGER_SIZE != 32)
  #error "BLOCKS_INTEGER_SIZE must be 8, 16 or 32 (see config.h)"
#endif

#if (BLOCKS_HASH_SIZE != 8) && (BLOCKS_HASH_SIZE != 16) && (BLOCKS_HASH_SIZE != 32)
  #error "BLOCKS_HASH_SIZE must be 8, 16 or 32 (see config.h)"
#endif

#if (BLOCKS_VARIABLE_INDEX_SIZE != 8) && (BLOCKS_VARIABLE_INDEX_SIZE != 16) && (BLOCKS_VARIABLE_INDEX_SIZE != 32)
  #error "BLOCKS_VARIABLE_INDEX_SIZE must be 8, 16 or 32 (see config.h)"
#endif
