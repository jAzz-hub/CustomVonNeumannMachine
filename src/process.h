// core:

// 1. instanciar o que está acontecendo no menu em uma classe com um único método chamado start
// 	1.1 start faz o que está acontecendo no menu começar até a etapa que carrega o asm na ram
// 	1.2 start deixa os atributos em estado pronto para que a thread consuma o processo.

// 2. criar uma função chamada execute
// 	2.1 execute faz com que uma thread receba um objeto do tipo start e rode ele na pipeline 
// 	criada na main
// 	2.2 

#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <string>
#include"./cpu/REGISTER_BANK.h"
#include"./cpu/CONTROL_UNIT.h"
#include"./memory/MAINMEMORY.h"
#include"./loader.h"

using namespace std;

struct process{

    const std::string input_program;
    int timestamp;
    const std::string state;
    int quantum;
    int id;
    int mem_addr

    process(input_program, timestamp, state, id, mem_addr)
    {
        this->input_program = input_program;
        this->timestamp = timestamp;
        this->state = state;
        this->quantum = 0;
        this->id = id;
        this->mem_addr = mem_addr;
    }

};

#endif