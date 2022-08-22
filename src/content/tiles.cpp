#include "../graphics/olcPixelGameEngine.h"
#include "../engine/world/tile.cpp"

class Tiles {
private:
    TileType *_buildTileType(std::string name, unsigned short maxHealth)
    {
        TileType *tileType = new TileType(name, maxHealth);
        return tileType;
    };

public:
    olc::vi2d GetSprite(Tile *tile)
    {
        // TODO if (tile->entity)
        // TODO if (tile->metadata)
        return tile->type->GetDefaultSprite(tile->defaultSpriteIndex);
    }
    olc::Pixel GetForeColor(Tile *tile)
    {
        // TODO if (tile->entity)
        // TODO if (tile->metadata)
        return tile->type->GetDefaultForeColor(tile->defaultForeColorIndex);
    }
    olc::Pixel GetBackColor(Tile *tile)
    {
        // TODO if (tile->entity)
        // TODO if (tile->metadata)
        return tile->type->GetDefaultBackColor(tile->defaultBackColorIndex);
    }

    void SetupVirginTile(Tile *tile, TileType *type)
    {
        tile->type = type;
        tile->defaultSpriteIndex = tile->type->GetRandomDefaultSpriteIndex();
        tile->defaultForeColorIndex = tile->type->GetRandomDefaultForeColorIndex();
        tile->defaultBackColorIndex = tile->type->GetRandomDefaultBackColorIndex();
    }

    TileType *empty = _buildTileType("empty", 0)
        ->AddDefaultSprite(olc::vi2d(11, 13))
        ->AddDefaultForeColor(0x000000FF)
        ->AddDefaultBackColor(0x000000FF);

    TileType *rock = _buildTileType("rock", 1000)
        ->AddDefaultSprite(olc::vi2d(11, 13))
        ->AddDefaultForeColor(0x3c2216FF)
        ->AddDefaultForeColor(0x451804FF)
        ->AddDefaultForeColor(0x4a2515FF)
        ->AddDefaultBackColor(0x000000FF);

    TileType *redSand = _buildTileType("rock", 1000)
        ->AddDefaultSprite(olc::vi2d(7, 15))
        ->AddDefaultSprite(olc::vi2d(14, 7))
        ->AddDefaultForeColor(0xc1440eFF)
        ->AddDefaultForeColor(0x9f3a0eFF)
        ->AddDefaultForeColor(0x7a2c0bFF)
        ->AddDefaultBackColor(0x000000FF);
};
