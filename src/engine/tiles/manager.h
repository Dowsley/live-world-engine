#pragma once

#include <string>
#include <map>

#include "../graphics/olcPixelGameEngine.h"
#include "functions.h"

class TileManager {
private:
    std::map<std::string, TileType*> naturalTileTypes;

public:
    TileManager();

    olc::vi2d GetSprite(Tile *tile);
    olc::Pixel GetForeColor(Tile *tile);
    olc::Pixel GetBackColor(Tile *tile);

    void SetupTile(Tile *tile, TileType *type, Organism *organism);

    TileType *AddNaturalTileType(std::string name, unsigned short maxHealth);

    TileType *GetNaturalTileType(std::string name);
};





