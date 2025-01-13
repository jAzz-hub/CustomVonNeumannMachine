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
            new_core.proc.set_state("waiting");
            new_core.proc.initialize_priorities();
            new_core.start();
            cores.push_back(new_core);
        }
    }
}

void PCB::turn_zombie(int core_index){
    this->cores[core_index].proc.set_state("stopped");
    this->zombies.push_back(this->cores[core_index]);

    if (core_index == 1)
        this->cores.erase(this->cores.begin() + 1);
    
    else
        this->cores.pop_front();

}

void PCB::zombie_check(){
    if (this->cores[0].stop_flag == true)
    {
        // Check if core is a zombie
        if (this->cores[0].zombie == true)  
            this->turn_zombie(0);
    
        // If core is not a zombie
        else
        {
            // Move core to the end of the queue
            this->cores.push_back(this->cores[0]);
            this->cores.pop_front();
        }
    }
    // Repeat for the second core
    if (this->cores[1].stop_flag == true)
    {   
        if (this->cores[1].zombie == true)
        {
            this->turn_zombie(1);
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


void PCB::zombies_info()
{
    for (const auto& zombie : zombies) {
        cout << "Quantum: " << zombie.proc.quantum << endl;
        cout << "Timestamp: " << zombie.proc.timestamp << endl;
        cout << "Program Name: " << zombie.proc.input_program << endl;
        cout << "End Program: " << zombie.endProgram << endl;
        cout << "Zombie: " << zombie.zombie << endl;
        cout << "Clock: " << zombie.clock << endl;
        cout << "Counter: " << zombie.counter << endl;
        cout << "-------------------------" << endl;
    }
}

void PCB::cores_info()
{
    for (const auto& core : cores) {
        cout << "Quantum: " << core.proc.quantum << endl;
        cout << "Timestamp: " << core.proc.timestamp << endl;
        cout << "Program Name: " << core.proc.input_program << endl;
        cout << "End Program: " << core.endProgram << endl;
        cout << "Zombie: " << core.zombie << endl;
        cout << "Clock: " << core.clock << endl;
        cout << "Counter: " << core.counter << endl;
        cout << "-------------------------" << endl;
    }
}