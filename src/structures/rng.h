#pragma once

#include <random>
#include <cstdint>

class Rng {
private:
    uint64_t seed = 0;
    std::mt19937 gen;
public:
    Rng(uint64_t seed);

    uint64_t GetSeed();
    void SetSeed(uint64_t seed);

    int RandRangeInt(int min, int max);
};
