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
#include <random>
#include"./cpu/REGISTER_BANK.h"
#include"./cpu/CONTROL_UNIT.h"
#include"./memory/MAINMEMORY.h"
#include"./loader.h"

using namespace std;

struct process{

    enum STATE {
        running,
        waiting,
        stopped,
    };

    enum PRIORITY
    {
        high,
        medium,
        low,
    };

    std::string input_program;
    int timestamp = 0;
    std::string state;
    std::string priority;
    int quantum;
    int id;
    int mem_addr;

    process(const std::string& input_program, int quantum, const std::string& state, int id, int mem_addr)
    : input_program(input_program), quantum(quantum), state(state), id(id), mem_addr(mem_addr)
    {
        this->timestamp = 0;
        
	//Gerando o id por casting com as 2 primeiras letras da string que dá nome ao programa de entrada
        for (size_t i = 0; i < this->input_program.size() && i < 3; ++i) {
            id = id * 100 + static_cast<int>(input_program[i]);
            this->id = id;
        }
    }

    process() = default;
    process(const process&) = default;
    process& operator=(const process&) = default;
    process(process&&) noexcept = default;
    process& operator=(process&&) noexcept = default;
    void print_attributes() const;
    void set_state(const std::string& state);    
    void initialize_priorities();
};

#endif


