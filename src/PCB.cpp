#include "PCB.h"

PCB::PCB(const std::vector<std::string>& input_programs) {
    int id_counter = 0;
    for (const auto& program : input_programs) {
        if (cores.size() < 10) {
            core new_core;
            new_core.ram = MainMemory(2048, 2048);
            new_core.registers = REGISTER_BANK();
            new_core.UC = Control_Unit();
            new_core.counterForEnd = 5;
            new_core.counter = 0;
            new_core.clock = 0;
            new_core.endProgram = false;
            new_core.data = Instruction_Data();
            new_core.proc.quantum = 20;
            new_core.proc.input_program = program;
            new_core.proc.state = "waiting";
            new_core.proc.id = id_counter++;
            new_core.start();
            cores.push_back(new_core);
        }
    }
}

void PCB::ZombieCheck(){
    if (this->cores[0].stop_flag == true)
    {
        if (this->cores[0].zombie == true)
        {
            this->zombies.push_back(this->cores[0]);
            this->cores.pop_front();
        }
        else
        {
            // Move core to the end of the queue
            this->cores.push_back(this->cores[0]);
            this->cores.pop_front();
        }
    }

    if (this->cores[1].stop_flag == true)
    {   
        if (this->cores[1].zombie == true)
        {
            this->zombies.push_back(this->cores[1]);
            this->cores.erase(this->cores.begin() + 1);
        }
        else
        {
            // Move core to the end of the queue
            this->cores.push_back(this->cores[1]);
            this->cores.erase(this->cores.begin() + 1);
        }
    }

    if (this->cores.empty())
    {
        cout << "All cores have been processed." << endl;
        return;
    }
}