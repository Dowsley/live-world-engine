#pragma once

#include <vector>
#include <tuple>

#include "../engine/olcPixelGameEngine.h"
#include "../structures/index.h"
#include "../creatures/manager.h"
#include "../tiles/registry.h"

class TileType;
class Tile;
class Creature;

class World
{
private:
    // Utils
    Vec3 dimensions;

    TileRegistry tileRegistry;
    std::unique_ptr<CreatureManager> creatureManager;
    Tile *map;


    std::tuple<Tile*, Creature*> _getTileAndCreature(const Vec3 &pos) const;
    Tile* _getTile(const Vec3 &pos) const;
    void _setTile(const Vec3 &pos, TileType *type);
    void _swapTiles(Tile *tile1, Tile *tile2);
    bool _isInBounds(const Vec3 &pos) const;

public:
    World(Vec3 dimensions);
    ~World();

    int GetHeight() const;
    int GetWidth() const;
    int GetDepth() const;
    const Vec3& GetDimensions() const;

    bool IsThereCreatureAt(const Vec3 &pos) const;

    const Vec2& GetTileSprite(const Vec3 &pos) const;
    const Color& GetTileForeColor(const Vec3 &pos) const;
    const Color& GetTileBackColor(const Vec3 &pos) const;
    TileType* GetTileType(const Vec3 &pos) const;
    std::string GetTileTypeName(const Vec3 &pos) const;

    void Update();
    void Generate();
    void GenerateTestBiome();
};
