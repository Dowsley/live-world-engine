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

public:
    World(Vec3 dimensions);
    ~World();

    int Flatten3DCoords(const Vec3 &pos) const;
    int Flatten2DCoords(const Vec2 &pos) const;

    int GetHeight() const;
    int GetWidth() const;
    int GetDepth() const;

    bool IsThereCreatureAt(const Vec3 &pos) const;
    Tile* GetTile(const Vec3 &pos) const;
    void SetTile(const Vec3 &pos, TileType *type);
    void SwapTiles(Tile *tile1, Tile *tile2);
    bool IsInBounds(const Vec3 &pos) const;

    const Vec2& GetTileSprite(const Vec3 &pos) const;
    const Color& GetTileForeColor(const Vec3 &pos) const;
    const Color& GetTileBackColor(const Vec3 &pos) const;
    TileType* GetTileType(const Vec3 &pos) const;
    std::string GetTileTypeName(const Vec3 &pos) const;

    void Update();
    void Generate();
    void GenerateTestBiome();
};
