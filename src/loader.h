#include"./memory/MAINMEMORY.h"
#include <string>

void loadProgram(const std::string& inputFile, MainMemory & ram); 
void loadProgramInRam(const std::string& inputFile, MainMemory & ram);
void loadProgramInCache(const std::string& inputFile, Cache & mem);