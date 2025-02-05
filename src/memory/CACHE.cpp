#include "CACHE.h"

uint32_t Cache::read(uint32_t address){
    // Verifica se o endereço está na cache
    if(cache_map.find(address) != cache_map.end()){
        // Atualiza a ordem de acesso (move para o final da lista)
        lru_list.splice(lru_list.end(), lru_list, cache_map[address]);
        return cache_map[address]->second; // Retorna o dado da cache
    } else {
        // Cache miss: carrega o dado da memória principal
        uint32_t data = this->aux_ram.ReadMem(address);

        // Se a cache estiver cheia, remove o LRU
        if(lru_list.size() >= size) {
            uint32_t lru_address = lru_list.front().first;
            cache_map.erase(lru_address);
            lru_list.pop_front();
        }

        // Adiciona o novo dado na cache
        lru_list.push_back({address, data});
        cache_map[address] = std::prev(lru_list.end());
        return data; // Retorna o dado carregado
    }
}

void Cache::write(uint32_t address, uint32_t data) {
    // Verifica se o endereço está na cache
    if (cache_map.find(address) != cache_map.end()) {
        // Atualiza o dado na cache e a ordem de acesso
        cache_map[address]->second = data;
        lru_list.splice(lru_list.end(), lru_list, cache_map[address]);
    } else {
        // Se a cache estiver cheia, remove o LRU
        if (lru_list.size() >= size) {
            uint32_t lru_address = lru_list.front().first;
            cache_map.erase(lru_address);
            lru_list.pop_front();
        }

        // Adiciona o novo dado na cache
        lru_list.push_back({address, data});
        cache_map[address] = std::prev(lru_list.end());
    }

    // Escreve o dado na memória principal (write-through)
    this->aux_ram.WriteMem(address, data);
}

// bool Cache::EmptyLine(int i) const
// {
// //      if(words[i] == NULL) return 1;
//         for (int j = 0 ;j < NumOfj; j++)
//         {
//                 if(words[i][j].read() != 0)
//                         return false;
//         }
//         return true;

//         //      else return 0;
// }

// void Cache::InsertData(const uint32_t data, int iTarget, int jTarget)
// {
//     sleep(3);
//     bool hA = iTarget<NumOfi && jTarget<NumOfj;
//     bool hB = iTarget>=0 && jTarget>=0;


//     if (hA && hB)  words[iTarget][jTarget].write(data);

//     else printf("Os valores de inserção de i e j são muito grandes!!");
// }

// void Cache::EraseData(int iTarget, int jTarget)
// {
//     sleep(3);
//     bool hA = iTarget<NumOfi && jTarget<NumOfj;
//     bool hB = iTarget>=0 && jTarget>=0;

//     if (hA && hB) words[iTarget][jTarget].write(0);

//     else printf("Os valores para deleção de i e j são muito grandes!!");
// }


void Cache::WriteMem(const uint32_t address, const uint32_t data)
{
    sleep(500);
    if (address >= NumOfi * NumOfj) {
        printf("Endereço inválido!\n");
        return;
    }
    int iTarget = address / NumOfj; 
    int jTarget = address % NumOfj; 
    words[iTarget][jTarget].write(data);
}

const uint32_t Cache::ReadMem(const uint32_t address) {
    sleep(500);
    if (address >= NumOfi * NumOfj) {
        printf("Endereço inválido!\n");
        return -1; 
    }
    int iTarget = address / NumOfj; 
    int jTarget = address % NumOfj; 
    
    return words[iTarget][jTarget].read();
}
