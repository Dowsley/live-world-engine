#include "registry.h"

TileRegistry::TileRegistry()
{
    AddNaturalTileType("empty", 0)
        ->AddDefaultSprite(Vec2(12, 0))
        ->AddDefaultForeColor(0, 0, 128)
        ->AddDefaultBackColor(0, 0, 128);

    AddNaturalTileType("rock", 1000)
        ->AddDefaultSprite(Vec2(9, 32))
        ->AddDefaultForeColor(60, 5, 8)
        ->AddDefaultForeColor(69, 1, 6)
        ->AddDefaultForeColor(74, 6, 11)
        ->AddDefaultBackColor(0, 0 ,0)
        ->SetSurface();

    AddNaturalTileType("soil", 300)
        ->AddDefaultSprite(Vec2(9, 32))
        ->AddDefaultForeColor(40, 20, 0)
        ->AddDefaultBackColor(0, 0, 0)
        ->SetSurface();

    AddNaturalTileType("grass", 100)
        ->AddDefaultSprite(Vec2(14, 4))
        ->AddDefaultSprite(Vec2(15, 4))
        ->AddDefaultSprite(Vec2(15, 2))
        ->AddDefaultSprite(Vec2(16, 2))
        ->AddDefaultForeColor(53, 178, 58)
        ->AddDefaultBackColor(0, 0, 0)
        ->SetSurface();
}

const Vec2& TileRegistry::GetSprite(Tile *tile) const
{
    // TODO if (tile->metadata)
    return tile->type->GetDefaultSprite(tile->defaultSpriteIndex);
}
Color TileRegistry::TileRegistry::GetForeColor(Tile *tile) const
{
    // TODO if (tile->metadata)
    return tile->type->GetDefaultForeColor(tile->defaultForeColorIndex);
}
Color TileRegistry::GetBackColor(Tile *tile) const
{
    // TODO if (tile->metadata)
    return tile->type->GetDefaultBackColor(tile->defaultBackColorIndex);
}

void TileRegistry::SetupTile(Tile *tile, TileType *type)
{
    tile->type = type;
    tile->defaultSpriteIndex = tile->type->GetRandomDefaultSpriteIndex();
    tile->defaultForeColorIndex = tile->type->GetRandomDefaultForeColorIndex();
    tile->defaultBackColorIndex = tile->type->GetRandomDefaultBackColorIndex();
}

TileType *TileRegistry::AddNaturalTileType(std::string name, unsigned short maxHealth)
{
    TileType *tileType = BuildTileType(name, maxHealth);
    naturalTileTypes[name] = tileType;
    return tileType;
}

TileType *TileRegistry::GetNaturalTileType(std::string name) const
{
    auto it = naturalTileTypes.find(name);
    if(it != naturalTileTypes.end())
        return it->second;
    return nullptr;
}
