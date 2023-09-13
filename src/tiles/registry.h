#pragma once

#include <string>
#include <unordered_map>

#include "tile.h"
#include "loader.h"

#include "../structures/color.h"
#include "../structures/vec2.h"

class TileRegistry {
public:
    explicit TileRegistry(const std::string &path);
    ~TileRegistry();

    TileType* GetTypeById(const std::string &id) const;
    void ReloadTiles(); // Use this to reload tiles if the files are updated.

private:
    void _loadTiles();

    std::unordered_map<std::string, TileType*> tileTypes;
    TileLoader loader;
};
