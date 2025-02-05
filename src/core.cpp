#include "core.h"

// core::core(MainMemory memory, REGISTER_BANK registers, Control_Unit uc, int cForEnd, int counter, int clock, bool endP, Instruction_Data instruction_D, process proc, bool cache, Cache cache_mem)
// {    
//     this->cache = cache;
//     this->registers = REGISTER_BANK();
//     this->UC = Control_Unit();
//     this->counterForEnd = 5;
//     this->counter = 0;
//     this->clock = 0;
//     this->endProgram = false;
//     this->data = Instruction_Data();
//     this->proc = process();
//     this->cache = false;
//     this->ram = MainMemory(2048, 2048);
//     this->instructions = std::vector<std::string>();
// }

void core::start() {
        loadProgramInRam(this->proc.input_program, this->ram, &this->core_instructions);
        
        // iterar sobre core_instructions
        for (auto instruction : this->core_instructions) {
            std::cout << instruction << std::endl;
        }
        cout<<endl;
        cout<<endl;
}


void core::setProcess(process &proc) {
    this->proc = proc;
}

core& core::running_asm(string scheduller, int similarity_caching_time)
{
    int reference_of_time; 
    if (scheduller == "RR" || scheduller == "FCFS")
    {
        reference_of_time = this->proc.quantum;
    }
    else if (scheduller == "SJF")
    {
        reference_of_time = this->proc.burst_time;
    }
    else
    {
        cout << "Invalid scheduller" << endl;
    }
    
    this->proc.state = "running";
    int quantum_reference = 0;
    bool stop_flag = false; //= ((this->clock%this->proc.quantum == 0) && (this->clock!=0)) && (this->proc.timestamp!=0); // false na primeira iteração 
    //roda a pipeline
    while(this->counterForEnd > 0 && !this->zombie)
    {
        
        if (!stop_flag)
        {       
            if(this->counter >= 4 && this->counterForEnd >= 1){
                //chamar a instrução de write back
                usleep(similarity_caching_time);
                stop_flag = (quantum_reference%reference_of_time == 0) && (quantum_reference!=0);
                this->UC.Write_Back(this->UC.data[ this->counter - 4 ], this->ram, this->registers);
            }
            if(this->counter >= 3 && this->counterForEnd >= 2){
                usleep(similarity_caching_time/2);
                //chamar a instrução de memory_acess da unidade de controle
                stop_flag = (quantum_reference%reference_of_time == 0) && (quantum_reference!=0);
                this->UC.Memory_Acess(this->registers, this->UC.data[ this->counter - 3 ], this->ram);
            }

            if(this->counter >= 2 && this->counterForEnd >= 3){
                usleep((similarity_caching_time/5)- 100);
                //chamar a instrução de execução da unidade de controle
                stop_flag = (quantum_reference%reference_of_time == 0) && (quantum_reference!=0);
                this->UC.Execute(this->registers,this->UC.data[ this->counter - 2 ], this->counter, this->counterForEnd, this->endProgram, this->ram);
            }

            if(this->counter >= 1 && this->counterForEnd >= 4){
                
                usleep(similarity_caching_time/3);
                //chamar a instrução de decode da unidade de controle
                stop_flag = (quantum_reference%reference_of_time == 0) && (quantum_reference!=0);
                this->UC.Decode(this->registers, this->UC.data[ this->counter-1 ]);
            }
            // Counter cresce quando a primeira instrução que rodou
            //é novamente consumida pela thread A e assim o data se torna um vector de tamanho 2
            // Contudo é requisitado seu elemento que está no índice 2(3º elemento [3])
            //Resultado? Segmentation fault
            
            if(this->counter >= 0 && this->counterForEnd == 5){
                usleep(similarity_caching_time/2);
                //chamar a instrução de fetch da unidade de controle
                stop_flag = (quantum_reference%reference_of_time == 0) && (quantum_reference!=0);
                this->UC.data.push_back(this->data) ;
                this->UC.Fetch(this->registers, this->endProgram, this->ram);
            }
        }
        this->proc.timestamp += 1; 
        this->counter += 1;
        this->clock += 1;
        quantum_reference += 1;
        
        if(this->endProgram == true){
            this->counterForEnd=-1;
            this->stop_flag = true;
            this->zombie = true;
        }

        if((quantum_reference%reference_of_time == 0) && (quantum_reference!=0)){
            this->counterForEnd -= 1;
            this->stop_flag = true;
            return *this;
        }        
    }
    return *this;
}
