#include "functions.h"

TileType *BuildTileType(std::string name, unsigned short maxHealth)
{
    TileType *tileType = new TileType(name, maxHealth);
    return tileType;
}