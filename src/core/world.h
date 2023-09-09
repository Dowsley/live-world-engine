#ifndef WORLD_H
#define WORLD_H

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


    std::tuple<Tile*, Creature*> _getTileAndCreature(const Vec3 &pos);

public:
    World(Vec3 dimensions);
    ~World();

    int Flatten3DCoords(const Vec3 &pos);
    int Flatten2DCoords(const Vec2 &pos);

    int GetHeight();
    int GetWidth();
    int GetDepth();

    bool IsThereCreatureAt(const Vec3 &pos);
    Tile* GetTile(const Vec3 &pos);
    void SetTile(const Vec3 &pos, TileType *type);
    void SwapTiles(Tile *tile1, Tile *tile2);
    bool IsInBounds(const Vec3 &pos);

    const Vec2& GetTileSprite(const Vec3 &pos);
    Color GetTileForeColor(const Vec3 &pos);
    Color GetTileBackColor(const Vec3 &pos);
    TileType* GetTileType(const Vec3 &pos);
    std::string GetTileTypeName(const Vec3 &pos);

    void Update();
    void Generate();
    void GenerateTestBiome();
};

#endif