#include <queue>
#include <string>
#include "core.h"

struct PCB {
    std::queue<core> cores;
    std::queue<core> zombies;

    PCB(const std::vector<std::string>& input_programs);
};
