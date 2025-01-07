#include "process.h"

void process::print_attributes() const {
    std::cout<<this->input_program<<std:: endl;
    std::cout<<this->timestamp<<std:: endl;
    std::cout<<this->state<<std:: endl;
    std::cout<<this->quantum<<std:: endl;
    std::cout<<this->id<<std:: endl;
    std::cout<<this->mem_addr<<std:: endl;
}

