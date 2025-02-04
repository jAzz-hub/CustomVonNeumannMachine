#ifndef CACHE_H
#define CACHE_H


#include "MEMORYCELL.h"
#include "MAINMEMORY.h"
#include "stdbool.h"


using namespace std;



struct Cache{
	int NumOfj;
	int NumOfi;
	MemoryCell **words;

	int size = 2048;

	std::list<std::pair<uint32_t, uint32_t>> lru_list; 

    std::unordered_map<uint32_t, std::list<std::pair<uint32_t, uint32_t>>::iterator> cache_map; 

    MainMemory& main_memory;


	Cache() : NumOfj(size), NumOfi(size), words(NULL), main_memory(main_memory){}


	Cache(int NumOfj, int NumOfi, MainMemory& main_memory) : main_memory(main_memory) {

		this->NumOfi = NumOfi;
		this->NumOfj = NumOfj;
		words =  (MemoryCell**)malloc( sizeof(MemoryCell*) * this->NumOfi);

		for(uint32_t k = 0; k<NumOfi ; k++)
		{
			words[k] = (MemoryCell*)malloc(sizeof(MemoryCell) * this->NumOfj);
		
			
		}

		for(uint32_t i = 0 ; i < NumOfi ; i++ )
			for(uint32_t j = 0 ; j< NumOfj ; j++)
				words[i][j].write(0);
		
	}

	void InsertData(const uint32_t data, int iTarget, int jTarget);
	void EraseData(int iTarget, int jTarget);
	bool EmptyLine(int i) const;
	void WriteMem(const uint32_t address, const uint32_t data);
	const uint32_t ReadMem(const uint32_t address);
	uint32_t read(uint32_t address);
	void write(uint32_t address, uint32_t data);

//	void ShowBit(int NumOfj, int NumOfi);
//	void WriteBit(REGISTER value, int iTarget, int jTarget);

};
#endif
