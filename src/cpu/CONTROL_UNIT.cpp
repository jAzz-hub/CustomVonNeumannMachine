#include "CONTROL_UNIT.h"

//PIPELINE

void Control_Unit::Fetch(REGISTER_BANK &registers, bool &endProgram){
    //Aqui são as ações para colocar a próxima instrução de prontidão
    const uint32_t instruction = registers.ir.read();
    if(instruction == 00000000000000000000000000001100)
    {
        endProgram = true;
        return;
    }
    registers.mar.write(registers.pc.value);
    //chamar a memória com a posição do pc e inserir em um registrador
    //registers.ir.write(aqui tem de ser passado a instrução que estiver na RAM);
    registers.pc.write(registers.pc.value += 1);//incrementando o pc 
}

void Control_Unit::Decode(REGISTER_BANK &registers, Temporary_Data &data){
    //Daqui vai ter de ser identificado o que fazer

    const uint32_t instruction = registers.ir.read();
    // tenho de converte o valor de 32 bits para binario e separar cada uma das partes para fazer a análise


    data.tarefa_a_ser_feita_pela_ula = Identificacao_instrucao(instruction,registers);
    if(data.tarefa_a_ser_feita_pela_ula != "LW" && data.tarefa_a_ser_feita_pela_ula != "LWA" && data.tarefa_a_ser_feita_pela_ula != "ST" &&  data.tarefa_a_ser_feita_pela_ula != "BME" && data.tarefa_a_ser_feita_pela_ula != "BMA" && data.tarefa_a_ser_feita_pela_ula != "BMAI" && data.tarefa_a_ser_feita_pela_ula != "BMEI"){
        // se entrar aqui é porque tem de carregar registradores, que estão especificados na instrução
        data.code_first_register = Pick_First_Code_Register(instruction);
        data.code_second_register = Pick_Second_Code_Register(instruction);
        data.code_third_register = Pick_Third_Code_Register(instruction);
        data.addressRAMResult = Pick_Adress_Result(instruction);

    }else if(data.tarefa_a_ser_feita_pela_ula == "LW" && data.tarefa_a_ser_feita_pela_ula == "LWA" && data.tarefa_a_ser_feita_pela_ula == "ST")
    {
        data.code_first_register = Pick_Code_Register_Load(instruction);
        data.addressRAMResult = Pick_Adress_Result(instruction);
    }else if(data.tarefa_a_ser_feita_pela_ula == "BME" && data.tarefa_a_ser_feita_pela_ula == "BMA" && data.tarefa_a_ser_feita_pela_ula == "BMAI" && data.tarefa_a_ser_feita_pela_ula == "BMEI"){
        data.code_first_register = Pick_First_Code_Register(instruction);
        data.code_second_register = Pick_Second_Code_Register(instruction);
        data.addressRAMResult = Pick_Adress_Result(instruction);
    }

    return;
}

void Control_Unit::Execute(REGISTER_BANK &registers,Temporary_Data &data, int &counter){
    /*Daqui tem de ser chamado o que tiver de ser chamado*/

    if(data.tarefa_a_ser_feita_pela_ula != "LW" && data.tarefa_a_ser_feita_pela_ula != "LWV" && data.tarefa_a_ser_feita_pela_ula != "ST" && data.tarefa_a_ser_feita_pela_ula != "BME" && data.tarefa_a_ser_feita_pela_ula != "BMA" && data.tarefa_a_ser_feita_pela_ula != "BMAI" && data.tarefa_a_ser_feita_pela_ula != "BMEI"){
        Execute_Aritmetic_Operation(registers, data);
    }else if(data.tarefa_a_ser_feita_pela_ula == "BME" && data.tarefa_a_ser_feita_pela_ula == "BMA" && data.tarefa_a_ser_feita_pela_ula == "BMAI" && data.tarefa_a_ser_feita_pela_ula == "BMEI"){
        Execute_Loop_Operation(registers, data, counter);
    }
}

void Control_Unit::Memory_Acess(REGISTER_BANK &registers,Temporary_Data &data){

    //aqui devem ser executadas as intruções de LOAD de fato

}

void Control_Unit::Write_Back(Temporary_Data &data){

    //aqui devem ocorrer qualquer uma das intruções de escrita na RAM
    if(data.tarefa_a_ser_feita_pela_ula == "ST"){
        //aqui tem de ser feito a escrita na RAM
        //Ram.insert[data.addressRAMResult] = registers.acessoLeituraRegistradores[data.code_third_register]();
    }

    return;

}

string Control_Unit::Identificacao_instrucao(const uint32_t instruction, REGISTER_BANK &registers){


    //instrução do tipo j
        string string_instruction = to_string(instruction);
        char first_check = 'x'; // → indica que tem endereço na instrução
        char second_check = 'v'; // → indica que tem endereço na instrução
        string instruction_type = "";

    if(string_instruction.find(first_check) != string::npos){
        //instrução do tipo j
        if(string_instruction.find(second_check) != string::npos){
            // LOAD de vetor
            instruction_type = "LWA";
        }
        else if(string_instruction.find("100011") != string::npos){
            // LOAD
            instruction_type = "LW";
        }else{
            // STORE
            instruction_type = "ST";
        }
    }else{

        //identificação das instruções do tipo R

        unsigned long long int opcode = instruction & 0b11111100000000000000000000111111;

        switch (opcode)
        {
        case 0b00000000000000000000000000100000:
            //instrução de ADD 
            instruction_type = "ADD";
            break;

        case 0b00000000000000000000000000100010:
            //instrução de SUB
            instruction_type = "SUB";
            break;

        case 0b00000000000000000000000000011000:
            //instrução de MUL
            instruction_type = "MUL";
            break;

        case 0b00000000000000000000000000011010:
            //instrução de DIV, neste caso teremos registradores especificos a serem usados
            instruction_type = "DIV";
            break;

        default:

             
                
            break;
        }
    }


} 

string Control_Unit::Pick_Adress_Result(const uint32_t instruction)
{
    string copia_instrucao = to_string(instruction);
    string code;
    for(int i = 11; i < 17; i++){
        code[i] = copia_instrucao[i];
    }

    return code;
}

string Control_Unit::Pick_Third_Code_Register(const uint32_t instruction){
    string copia_instrucao = to_string(instruction);
    string code;
    for(int i = 18; i < 23; i++){
        code[i] = copia_instrucao[i];
    }

    return code;
}

string Control_Unit::Pick_Second_Code_Register(const uint32_t instruction){
    string copia_instrucao = to_string(instruction);
    string code;
    for(int i = 13; i < 18; i++){
        code[i] = copia_instrucao[i];
    }

    return code;
}

string Control_Unit::Pick_First_Code_Register(const uint32_t instruction){
    string copia_instrucao = to_string(instruction);
    string code;
    for(int i = 8; i < 13; i++){
        code[i] = copia_instrucao[i];
    }

    return code;
}

void Control_Unit::Execute_Aritmetic_Operation(REGISTER_BANK &registers,Temporary_Data &data){

        ALU alu;
        if(data.tarefa_a_ser_feita_pela_ula == "ADD"){
            alu.A = registers.acessoLeituraRegistradores[data.code_first_register]();
            alu.B = registers.acessoLeituraRegistradores[data.code_second_register]();
            alu.result = registers.acessoEscritaRegistradores[data.code_third_register]();
            alu.op = ADD;
            alu.calculate();
        }else if(data.tarefa_a_ser_feita_pela_ula == "SUB"){
            alu.A = registers.acessoLeituraRegistradores[data.code_first_register]();
            alu.B = registers.acessoLeituraRegistradores[data.code_second_register]();
            alu.result = registers.acessoEscritaRegistradores[data.code_third_register]();
            alu.op = SUB;
            alu.calculate();
        }else if(data.tarefa_a_ser_feita_pela_ula == "MUL"){
            alu.A = registers.acessoLeituraRegistradores[data.code_first_register]();
            alu.B = registers.acessoLeituraRegistradores[data.code_second_register]();
            alu.result = registers.acessoEscritaRegistradores[data.code_third_register]();
            alu.op = MUL;
            alu.calculate();
        }else if(data.tarefa_a_ser_feita_pela_ula == "DIV"){
            alu.A = registers.acessoLeituraRegistradores[data.code_first_register]();
            alu.B = registers.acessoLeituraRegistradores[data.code_second_register]();
            alu.result = registers.acessoEscritaRegistradores[data.code_third_register]();
            alu.op = DIV;
            alu.calculate();
        }

        return;
}

void Control_Unit::Execute_Loop_Operation(REGISTER_BANK &registers,Temporary_Data &data, int &counter){
    
    ALU alu;
    if(data.tarefa_a_ser_feita_pela_ula == "BME"){
        alu.A = registers.acessoLeituraRegistradores[data.code_first_register]();
        alu.B = registers.acessoLeituraRegistradores[data.code_second_register]();
        alu.op = BME;
        alu.calculate();
        if(alu.result == 1){
            registers.pc.write(static_cast<uint32_t>(stoul(data.addressRAMResult)));
            counter = 0;
        }
    }else if(data.tarefa_a_ser_feita_pela_ula == "BMEI"){
        alu.A = registers.acessoLeituraRegistradores[data.code_first_register]();
        alu.B = registers.acessoLeituraRegistradores[data.code_second_register]();
        alu.op = BMEI;
        alu.calculate();
        if(alu.result == 1){
            registers.pc.write(static_cast<uint32_t>(stoul(data.addressRAMResult)));
            counter = 0;
        }
    }else if(data.tarefa_a_ser_feita_pela_ula == "BMA"){
        alu.A = registers.acessoLeituraRegistradores[data.code_first_register]();
        alu.B = registers.acessoLeituraRegistradores[data.code_second_register]();
        alu.op = BMA;
        alu.calculate();
        if(alu.result == 1){
            registers.pc.write(static_cast<uint32_t>(stoul(data.addressRAMResult)));
            counter = 0;
        }
    }else if(data.tarefa_a_ser_feita_pela_ula == "BMAI"){
        alu.A = registers.acessoLeituraRegistradores[data.code_first_register]();
        alu.B = registers.acessoLeituraRegistradores[data.code_second_register]();
        alu.op = BMAI;
        alu.calculate();
        if(alu.result == 1){
            registers.pc.write(static_cast<uint32_t>(stoul(data.addressRAMResult)));
            counter = 0;
        }
    }
}

