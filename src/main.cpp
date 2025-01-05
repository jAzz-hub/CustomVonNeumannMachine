#include"./cpu/REGISTER_BANK.h"
#include"./cpu/CONTROL_UNIT.h"
#include"./memory/MAINMEMORY.h"
#include"./loader.h"
#include"./core.h"
#include"./process.h"
#include<pthread.h>
using namespace std;


// Processo é criado

// Processo recebe uma UC

// Thread fica pronta.

// Thread começa a consumir um processo.

// Thread 

// Thread fica sabendo qual das UC ela vai atacar.

// Thread ataca a UC que ela deveria.

void *tico(void *arg)
{
    printf("tico\n");
    return NULL;

}

void teco()
{
    printf("teco\n");
}

int main(int argc, char* argv[]){

    if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
    return 1;
    }

    MainMemory ram = MainMemory(2048,2048);				//  1º  Cria-se uma variável do tipo MainMemory com 2048 linhas e 2048 colunas.
    REGISTER_BANK registers;
    Control_Unit UC;
    int counterForEnd = 5;
    int counter = 0;
    int clock = 0;
    bool endProgram = false;
    Instruction_Data data;

    process p1 = process(argv[1], 3, "novo", 4828, 284);
    core c1 = core(ram, registers, UC, counterForEnd, counter, clock, endProgram, data, p1);
    core c2 = core(ram, registers, UC, counterForEnd, counter, clock, endProgram, data, p1);
    
    pthread_t t1 = pthread_create(&t1, NULL, c1.start(), NULL);
    pthread_t t2 = pthread_create(&t2, NULL, c2.start(), NULL);

    teco();

    c1.start();

    c1.running_asm();

    return 0;

}