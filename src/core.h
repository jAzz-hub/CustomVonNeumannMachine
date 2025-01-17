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
#include "memory/MAINMEMORY.h"
#include "cpu/REGISTER_BANK.h"
#include "cpu/CONTROL_UNIT.h"
#include "process.h"
#include "./loader.h"

using namespace std;

struct core {

    MainMemory ram = MainMemory(2048,2048);				//  1º  Cria-se uma variável do tipo MainMemory com 2048 linhas e 2048 colunas.
    REGISTER_BANK registers;
    Control_Unit UC;
    int counterForEnd = 5;
    int counter = 0;
    int clock = 0;
    bool endProgram = false;
    bool zombie = false;
    bool stop_flag = false;
    Instruction_Data data;
    process proc; // Renamed to avoid conflict

    core(MainMemory memory, REGISTER_BANK registers, Control_Unit uc, int cForEnd, int counter, int clock, bool endP, Instruction_Data instruction_D, process proc)
        : ram(memory), registers(registers), UC(uc), counterForEnd(cForEnd), counter(counter), clock(clock), endProgram(endP), data(instruction_D), proc(proc)
    {
    }

    core() : ram(2048,2048), registers(), UC(), counterForEnd(5), counter(0), clock(0), endProgram(false), data(), proc("", 0, "", 0, 0) {}

    void start();
    core& running_asm(string scheduller);
    void execute();
    void setProcess(process &proc);

    core(const core&) = default;
    core& operator=(const core&) = default;
    core(core&&) noexcept = default;
    core& operator=(core&&) noexcept = default;
};
#endif

