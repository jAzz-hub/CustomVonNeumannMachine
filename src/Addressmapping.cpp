#include "Addressmapping.h"

void Addressmapping::generate_addresses(int num_cores) {
    addresses.resize(num_cores);
    std::iota(addresses.begin(), addresses.end(), 0);
}

void Addressmapping::sort_addresses(const std::vector<int>& burst_times) {
    std::sort(addresses.begin(), addresses.end(), [&](int a, int b) {
        return burst_times[a] < burst_times[b];
    });
}

int Addressmapping::get_address(int index) const {
    return addresses[index];
}
