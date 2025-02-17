#ifndef ADDRESS_MAPPING_H
#define ADDRESS_MAPPING_H

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <numeric> // for std::iota

using namespace std;

struct AddressMapping {
    unordered_map<string, int> address_map;
    vector<int> addresses;

    void AddressMapping::generate_addresses(const vector<string>& instructions);
    void AddressMapping::sort_addresses(const vector<string>& instructions);
    int AddressMapping::get_address(int index) const;
};

#endif
