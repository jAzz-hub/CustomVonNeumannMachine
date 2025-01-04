#include "core.h"

void core::start() {
    loadProgram(this->proc.input_program, this->ram);
}

void core::running_asm()
{
    while(this->counterForEnd > 0)
    {
        if(this->counter >= 4 && this->counterForEnd >= 1){
            //chamar a instrução de write back
            this->UC.Write_Back(this->UC.data[ this->counter - 4 ], this->ram, this->registers);
        }
        if(this->counter >= 3 && this->counterForEnd >= 2){
            //chamar a instrução de memory_acess da unidade de controle
            this->UC.Memory_Acess(this->registers, this->UC.data[ this->counter - 3 ], this->ram);
        }                
        if(this->counter >= 2 && this->counterForEnd >= 3){
            //chamar a instrução de execução da unidade de controle
            this->UC.Execute(this->registers,this->UC.data[ this->counter - 2 ], this->counter, this->counterForEnd, this->endProgram, this->ram);
        }
        if(this->counter >= 1 && this->counterForEnd >= 4){
            //chamar a instrução de decode da unidade de controle
            this->UC.Decode(this->registers, this->UC.data[ this->counter-1 ]);
        }
        if(this->counter >= 0 && this->counterForEnd == 5){
            //chamar a instrução de fetch da unidade de controle
            this->UC.data.push_back(this->data) ;
            this->UC.Fetch(this->registers, this->endProgram, this->ram);
        }
        this->counter += 1;
        this->clock += 1;

        if(this->endProgram == true){
            this->counterForEnd =- 1;
        }
    }
}
