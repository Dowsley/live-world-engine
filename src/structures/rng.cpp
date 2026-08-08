#include "rng.h"

Rng::Rng(uint64_t seed) {
   SetSeed(seed);
}

uint64_t Rng::GetSeed() {
    return this->seed;
}

void Rng::SetSeed(uint64_t seed) {
    this->seed = seed;
    gen = std::mt19937(seed);
}

int Rng::RandRangeInt(int min, int max) {
    std::uniform_int_distribution<> dist(min, max);
    return dist(this->gen);
}

