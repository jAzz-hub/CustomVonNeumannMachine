#include "PCB.h"

// fazer com que ao invés de grandes structs serem ordenadas
// que sejam ordenadas labels, para que o programa ganhe performance
// de modo que essas labels representem a paginação.


PCB::PCB(const vector<string>& input_programs, string scheduller, bool cache) {
    int id_counter = 0;
    this->scheduller = scheduller;
    for (const auto& program : input_programs) {
        if (cores.size() < 10) {
            core new_core;
            MainMemory memory(2048, 2048);
            new_core.registers = REGISTER_BANK();
            new_core.UC = Control_Unit();
            new_core.counterForEnd = 5;
            new_core.counter = 0;
            new_core.clock = 0;
            new_core.endProgram = false;
            new_core.data = Instruction_Data();
            chrono_initializer(&new_core, program);
            new_core.proc.input_program = program;
            new_core.proc.state = "waiting";
            new_core.proc.id = id_counter++;
            new_core.proc.set_state("waiting");
            new_core.proc.initialize_priorities();
            new_core.start();
            cores.push_back(new_core);
        }
    }
    address_mapping.generate_addresses(cores.size());
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
        cout<< "Burst Time: " << zombie.proc.burst_time << endl;
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
        cout<< "Burst Time: " << core.proc.burst_time << endl;
        cout << "Timestamp: " << core.proc.timestamp << endl;
        cout << "Program Name: " << core.proc.input_program << endl;
        cout << "End Program: " << core.endProgram << endl;
        cout << "Zombie: " << core.zombie << endl;
        cout << "Clock: " << core.clock << endl;
        cout << "Counter: " << core.counter << endl;
        cout<< "stop_condition" << core.stop_flag <<endl;
        cout << "-------------------------" << endl;
    }
}

void PCB::chrono_initializer( core *new_core, string program)
{
    if (this->scheduller == "SJF")
    {
        new_core->proc.burst_time = burster(program); // Faz com que cada input_program tenha um burst time diferente
    }
    else if (this->scheduller == "RR")
    {
        new_core->proc.quantum = 20; // Quantum de 20ms para todos os processos
    }
    else if(this->scheduller == "FCFS")
    {
        new_core->proc.quantum = 100; // Processa os processos até eles terminarem
    }
}


int PCB::burster(string program)
{
    if (program == "outputs2/exout.bin")
    {
        return 23;
    }
    else if(program == "outputs2/outex.bin")
    {
        return 23;
    }
    else if(program == "outputs2/outextwo.bin")
    {
        return 23;
    }
    else if(program == "outputs2/outioop.bin")
    {
        return 16;
    }
    else if(program == "outputs2/outmultanddivide.bin")
    {
        return 20;
    }
    else if(program == "outputs2/outmultanddividetwo.bin")
    {
        return 20;
    }
    else if(program == "outputs2/outsumdec.bin")
    {
        return 20;
    }
    else if(program == "outputs2/outsumdeccesar.bin")
    {
        return 20;
    }
    else if(program == "outputs2/outsumsub.bin")
    {
        return 20;
    }
    else if(program == "outputs2/nopout.bin")
    {
        return 20;
    } 
    //sorteia um número entre 15 e 40
    else
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(15, 40);
        return dis(gen);
    }

}

//ordena os cores de acordo com seu valor de burst time
void PCB::sorting_cores() {
    vector<int> burst_times(cores.size());
    for (size_t i = 0; i < cores.size(); ++i) {
        burst_times[i] = cores[i].proc.burst_time;
    }
    address_mapping.sort_addresses(burst_times);
}

core& PCB::get_core(int address) {
    return cores[address];
}

bool PCB::SJF()
{
    return this->scheduller == "SJF";
}

bool PCB::RR()
{
    return this->scheduller == "RR";
}
