#include "pcb.h"

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
            new_core.process.quantum = 10;
            new_core.process.input_program = program;
            new_core.process.state = "waiting";
            new_core.process.id = id_counter++;
            new_core.start();
            cores.push(new_core);
        }
    }
}
