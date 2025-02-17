#ifndef ADDRESS_MAPPING_H
#define ADDRESS_MAPPING_H

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <numeric> // for std::iota

using namespace std;

struct Addressmapping {
    unordered_map<string, int> address_map;
    vector<int> addresses;

    void generate_addresses(int num_cores);
    void sort_addresses(const std::vector<int>& burst_times);
    int get_address(int index) const;
};

#endif
