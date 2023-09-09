#pragma once

#include <string>
#include <map>

#include "functions.h"
#include "../structures/color.h"
#include "../structures/vec2.h"

class TileRegistry {
private:
    std::map<std::string, TileType*> naturalTileTypes;

public:
    TileRegistry();

    const Vec2& GetSprite(Tile *tile);
    Color GetForeColor(Tile *tile);
    Color GetBackColor(Tile *tile);

    void SetupTile(Tile *tile, TileType *type);

    TileType *AddNaturalTileType(std::string name, unsigned short maxHealth);

    TileType *GetNaturalTileType(std::string name);
};
