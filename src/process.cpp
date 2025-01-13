#include "process.h"

void process::print_attributes() const {
    std::cout<<this->input_program<<std:: endl;
    std::cout<<this->timestamp<<std:: endl;
    std::cout<<this->state<<std:: endl;
    std::cout<<this->quantum<<std:: endl;
    std::cout<<this->id<<std:: endl;
    std::cout<<this->mem_addr<<std:: endl;
}

void process::set_state(const std::string& state) {
    this->state = state;
}

void process::initialize_priorities() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 2);

    this->priority = static_cast<process::PRIORITY>(dis(gen));
}