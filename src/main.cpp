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
    
    c1.start();
    
    pthread_t t1;
    pthread_create(&t1, NULL, tico, NULL);

    teco();

    c1.running_asm();

    return 0;


//   loadProgram(argv[1],ram);


//             while(counterForEnd > 0){
//                 if(counter >= 4 && counterForEnd >= 1){
//                     //chamar a instrução de write back
//                     UC.Write_Back(UC.data[counter - 4],ram,registers);
//                 }
//                 if(counter >= 3 && counterForEnd >= 2){
//                     //chamar a instrução de memory_acess da unidade de controle
//                     UC.Memory_Acess(registers, UC.data[counter - 3],ram);
// }                }
//                 if(counter >= 2 && counterForEnd >= 3){
//                     //chamar a instrução de execução da unidade de controle
//                     UC.Execute(registers,UC.data[counter - 2], counter, counterForEnd,endProgram,ram);
//                 }
//                 if(counter >= 1 && counterForEnd >= 4){
//                     //chamar a instrução de decode da unidade de controle
//                     UC.Decode(registers, UC.data[counter-1]);
//                 }
//                 if(counter >= 0 && counterForEnd == 5){
//                     //chamar a instrução de fetch da unidade de controle
//                     UC.data.push_back(data) ;
//                     UC.Fetch(registers, endProgram,ram);
//                 }
//                 counter += 1;
//                 clock += 1;
//                 if(endProgram == true){
//                     counterForEnd =- 1;
//                 }
//             }
        
      
       
//     return 0;
}
