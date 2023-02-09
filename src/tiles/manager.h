#ifndef TILE_MANAGER_H
#define TILE_MANAGER_H

#include <string>
#include <map>

#include "functions.h"
#include "../structures/color.h"
#include "../structures/vec2.h"

class TileManager {
private:
    std::map<std::string, TileType*> naturalTileTypes;

public:
    TileManager();

    Vec2 GetSprite(Tile *tile);
    Color GetForeColor(Tile *tile);
    Color GetBackColor(Tile *tile);

    void SetupTile(Tile *tile, TileType *type, Organism *organism);

    TileType *AddNaturalTileType(std::string name, unsigned short maxHealth);

    TileType *GetNaturalTileType(std::string name);
};

#endif
