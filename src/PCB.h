#ifndef PCB_H
#define PCB_H

#include <deque>
#include <string>
#include "core.h"

struct PCB {
    std::deque<core> cores;
    std::deque<core> zombies;

    PCB(const std::vector<std::string>& input_programs);
    void zombie_check();
    void zombies_info();
    void cores_info();
    void turn_zombie(int core_index);

};

#endif
