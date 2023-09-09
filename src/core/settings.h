#ifndef SETTINGS_H
#define SETTINGS_H

#if _WIN32
    #define CREATURE_REGISTRY_PATH_V "data\\creatures"
#else
    #define CREATURE_REGISTRY_PATH_V "data/creatures"
#endif

#include "../engine/olcPixelGameEngine.h"
#include "../structures/index.h"

namespace Settings {
    const Vec3 WORLD_DIMENSIONS = { 512, 512, 50 };
    const Vec2 TILE_SIZE = { 12, 12 };
    const Vec2 TILE_OFFSET = { 1, 1 };
    const Color FORE_PLACEHOLDER = olc::WHITE;
    const Color BACK_PLACEHOLDER = olc::BLACK;
    const int TICK_DURATION = 700;
    const std::string CREATURE_REGISTRY_PATH = CREATURE_REGISTRY_PATH_V;
}

#endif