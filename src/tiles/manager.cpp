#include "manager.h"

TileManager::TileManager()
{
    AddNaturalTileType("empty", 0)
        ->AddDefaultSprite(olc::vi2d(11, 13))
        ->AddDefaultForeColor(0, 0, 128)
        ->AddDefaultBackColor(0, 0, 128);

    AddNaturalTileType("rock", 1000)
        ->AddDefaultSprite(olc::vi2d(11, 13))
        ->AddDefaultForeColor(60, 5, 8)
        ->AddDefaultForeColor(69, 1, 6)
        ->AddDefaultForeColor(74, 6, 11)
        ->AddDefaultBackColor(0, 0 ,0)
        ->SetSurface();

    AddNaturalTileType("soil", 1000)
        ->AddDefaultSprite(olc::vi2d(7, 15))
        ->AddDefaultSprite(olc::vi2d(14, 7))
        ->AddDefaultForeColor(122, 5, 21)
        ->AddDefaultForeColor(159, 9, 36)
        ->AddDefaultForeColor(193, 11, 51)
        ->AddDefaultBackColor(0, 0, 0)
        ->SetSurface();
}

olc::vi2d TileManager::GetSprite(Tile *tile)
{
    // TODO if (tile->entity)
    // TODO if (tile->metadata)
    return tile->type->GetDefaultSprite(tile->defaultSpriteIndex);
}
olc::Pixel TileManager::TileManager::GetForeColor(Tile *tile)
{
    // TODO if (tile->entity)
    // TODO if (tile->metadata)
    return tile->type->GetDefaultForeColor(tile->defaultForeColorIndex);
}
olc::Pixel TileManager::GetBackColor(Tile *tile)
{
    // TODO if (tile->entity)
    // TODO if (tile->metadata)
    return tile->type->GetDefaultBackColor(tile->defaultBackColorIndex);
}

void TileManager::SetupTile(Tile *tile, TileType *type, Organism *organism)
{
    tile->type = type;
    tile->defaultSpriteIndex = tile->type->GetRandomDefaultSpriteIndex();
    tile->defaultForeColorIndex = tile->type->GetRandomDefaultForeColorIndex();
    tile->defaultBackColorIndex = tile->type->GetRandomDefaultBackColorIndex();
    if (organism) {
        if (tile->metadata) {
            tile->metadata->SetOrganism(organism);
        } else {
            tile->metadata = new TileMetadata(tile, organism);
        }
    }
}

TileType *TileManager::AddNaturalTileType(std::string name, unsigned short maxHealth)
{
    TileType *tileType = BuildTileType(name, maxHealth);
    naturalTileTypes[name] = tileType;
    return tileType;
}

TileType *TileManager::GetNaturalTileType(std::string name)
{
    return naturalTileTypes[name];
}
