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

    const Vec2& GetSprite(Tile *tile) const;
    const Color& GetForeColor(Tile *tile) const;
    const Color& GetBackColor(Tile *tile) const;

    void SetupTile(Tile *tile, TileType *type);

    TileType *AddNaturalTileType(std::string name, unsigned short maxHealth);

    TileType *GetNaturalTileType(std::string name) const;
};
