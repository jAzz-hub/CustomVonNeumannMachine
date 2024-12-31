// core:

// 1. instanciar o que está acontecendo no menu em uma classe com um único método chamado start
// 	1.1 start faz o que está acontecendo no menu começar até a etapa que carrega o asm na ram
// 	1.2 start deixa os atributos em estado pronto para que a thread consuma o processo.

// 2. criar uma função chamada execute
// 	2.1 execute faz com que uma thread receba um objeto do tipo start e rode ele na pipeline 
// 	criada na main
// 	2.2 

#ifndef CORE_H
#define CORE_H

#include <iostream>
#include"./cpu/REGISTER_BANK.h"
#include"./cpu/CONTROL_UNIT.h"
#include"./memory/MAINMEMORY.h"
#include"./loader.h"

using namespace std;

struct core{

    MainMemory ram = MainMemory(2048,2048);				//  1º  Cria-se uma variável do tipo MainMemory com 2048 linhas e 2048 colunas.
    REGISTER_BANK registers;
    Control_Unit UC;
    int counterForEnd = 5;
    int counter = 0;
    int clock = 0;
    bool endProgram = false;
    Instruction_Data data;

    core(memory, registers, uc, cForEnd, counter, clock, endP, Instruciton_D)
    {
        this->ram = memory;
        this->registers = registers;
        this->uc = UC;
        this->counterForEnd = cForEnd;
        this->counter = counter;
        this->clock = clock;
        this->endProgram = endP;
        this->clock = clock;
        this->Instruciton_Data = Instruciton_D;
    }

    core(): MainMemory(2048,2048), REGISTER_BANK(), Control_Unit(), 5, 0, 0, false, Instruction_Data(){};

    void start(Process process,MainMemory ram);

};
