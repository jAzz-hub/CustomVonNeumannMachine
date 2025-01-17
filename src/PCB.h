#ifndef PCB_H
#define PCB_H

#include <deque>
#include <string>
#include "core.h"


struct PCB {
    std::deque<core> cores;
    std::deque<core> zombies;
    string scheduller;

    PCB(const std::vector<std::string>& input_programs, string scheduller);
    void zombie_check();
    void zombies_info();
    void cores_info();
    void turn_zombie(int core_index);
    void sorting_cores();
    void chrono_initializer(core *new_core, string program);
    int burster(string program);
    bool SJF();
    bool RR();
};

#endif
