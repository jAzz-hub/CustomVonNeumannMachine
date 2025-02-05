#include"./memory/CACHE.h"
#include <string>

void loadProgram(const std::string& inputFile, MainMemory & ram); 
void loadProgramInRam(const std::string& inputFile, MainMemory & ram,  std::vector<std::string> *instructions);
void loadProgramInCache(const std::string& inputFile, Cache & mem,  std::vector<std::string> *instructions);