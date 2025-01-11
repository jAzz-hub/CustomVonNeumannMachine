#include "core.h"

void core::start() {
    loadProgram(this->proc.input_program, this->ram);
}

void core::setProcess(process &proc) {
    this->proc = proc;
}

core& core::running_asm(int quantum)
{
    int quantum_reference = 0;
    bool stop_flag = false; //= ((this->clock%this->proc.quantum == 0) && (this->clock!=0)) && (this->proc.timestamp!=0); // false na primeira iteração 
    //roda a pipeline
    while(this->counterForEnd > 0 && !this->zombie)
    {
        if (!stop_flag)
        {       
            if(this->counter >= 4 && this->counterForEnd >= 1){
                //chamar a instrução de write back
                stop_flag = (quantum_reference%this->proc.quantum == 0) && (quantum_reference!=0);
                cout<<endl<<"SegF cfE = 1"<<endl;
                this->UC.Write_Back(this->UC.data[ this->counter - 4 ], this->ram, this->registers);
            }
            if(this->counter >= 3 && this->counterForEnd >= 2){
                //chamar a instrução de memory_acess da unidade de controle
                stop_flag = (quantum_reference%this->proc.quantum == 0) && (quantum_reference!=0);
                cout<<endl<<"SegF cfE = 2"<<endl;
                this->UC.Memory_Acess(this->registers, this->UC.data[ this->counter - 3 ], this->ram);
            }

            if(this->counter >= 2 && this->counterForEnd >= 3){
                //chamar a instrução de execução da unidade de controle
                stop_flag = (quantum_reference%this->proc.quantum == 0) && (quantum_reference!=0);
                cout<<endl<<"SegF cfE = 3"<<endl;
                this->UC.Execute(this->registers,this->UC.data[ this->counter - 2 ], this->counter, this->counterForEnd, this->endProgram, this->ram);
            }

            if(this->counter >= 1 && this->counterForEnd >= 4){
                //chamar a instrução de decode da unidade de controle
                stop_flag = (quantum_reference%this->proc.quantum == 0) && (quantum_reference!=0);
                cout<<endl<<"SegF cfE = 44444444"<<endl;
                this->UC.Decode(this->registers, this->UC.data[ this->counter-1 ]);
            }

            if(this->counter >= 0 && this->counterForEnd == 5){
                //chamar a instrução de fetch da unidade de controle
                stop_flag = (quantum_reference%this->proc.quantum == 0) && (quantum_reference!=0);
                this->UC.data.push_back(this->data) ;
                cout<<endl<<"SegF cfE = 5"<<endl;
                this->UC.Fetch(this->registers, this->endProgram, this->ram);
            }
            this->counter += 1;

        }
        this->proc.timestamp += 1; 
        // this->counter += 1;
        this->clock += 1;
        quantum_reference += 1;
        
        if(this->endProgram == true){
            this->counterForEnd=-1;
            this->zombie = true;
        }

        if((quantum_reference%this->proc.quantum == 0) && (quantum_reference!=0)){
            this->counterForEnd -= 1;
            this->stop_flag = true;
            return *this;
        }
        // Simular a condição de término do programa
        // if (this->counter % 100 == 0 || this-proc.timestamp % this->proc.quantum == 0) {
        //     this->endProgram = true;
        // }
        

    }
    return *this;
}


