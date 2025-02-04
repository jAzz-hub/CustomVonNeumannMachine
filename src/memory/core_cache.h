// core:

// 1. instanciar o que está acontecendo no menu em uma classe com um único método chamado start
// 	1.1 start faz o que está acontecendo no menu começar até a etapa que carrega o asm na ram
// 	1.2 start deixa os atributos em estado pronto para que a thread consuma o processo.

// 2. criar uma função chamada execute
// 	2.1 execute faz com que uma thread receba um objeto do tipo start e rode ele na pipeline 
// 	criada na main
// 	2.2 

#ifndef CORE_CACHE_H
#define CORE_CACHE_H

#include <iostream>
#include "memory/CACHE.h"
#include "cpu/REGISTER_BANK.h"
#include "cpu/CONTROL_UNIT.h"
#include "process.h"
#include "./loader.h"

using namespace std;

struct core_cache {
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

    core_cache(MainMemory memory, REGISTER_BANK registers, Control_Unit uc, int cForEnd, int counter, int clock, bool endP, Instruction_Data instruction_D, process proc)
        : ram(memory), registers(registers), UC(uc), counterForEnd(cForEnd), counter(counter), clock(clock), endProgram(endP), data(instruction_D), proc(proc)
    {
    }

    core_cache() : ram(2048,2048), registers(), UC(), counterForEnd(5), counter(0), clock(0), endProgram(false), data(), proc("", 0, "", 0, 0) {}

    void start();
    core_cache& running_asm(string scheduller);
    void execute();
    void setProcess(process &proc);

    core_cache(const core_cache&) = default;
    core_cache& operator=(const core_cache&) = default;
    core_cache(core_cache&&) noexcept = default;
    core_cache& operator=(core_cache&&) noexcept = default;
};
#endif

