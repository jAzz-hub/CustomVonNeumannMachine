#include <deque>
#include <string>
#include "core.h"

struct PCB {
    std::deque<core> cores;
    std::deque<core> zombies;

    PCB(const std::vector<std::string>& input_programs);
};
