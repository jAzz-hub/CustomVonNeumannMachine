//
// Created by czarhrs on 10/10/24.
//

#ifndef REGISTER_H
#define REGISTER_H
#include <time.h>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <bitset>
#include <cinttypes>
#include <unistd.h>
#include <time.h>
#include <stdio.h> 
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unordered_set>
#include <chrono>
#include <set>
#include <list>



using namespace std;

 

struct REGISTER {
    uint32_t value;

    REGISTER() : value(0x0000) {}

    void write(uint32_t new_value);

    // [[nodiscard]]: proibe a pesoa de discartar o valor de retorno da função
    [[nodiscard]] uint32_t read() const;
    [[nodiscard]] uint32_t reverse_read() const;
};


#endif //REGISTER_H
