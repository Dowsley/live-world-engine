#pragma once

#include <tuple>

#include "settings.h"

#include "../core/pathfinding.h"

#include "../engine/olcPixelGameEngine.h"
#include "../structures/index.h"
#include "../creatures/manager.h"
#include "../tiles/manager.h"
#include "../tiles/registry.h"

class TileType;
struct Tile;
class Creature;

class World
{
private:
    Vec3 dimensions;
    Tile *map;

    std::unique_ptr<CreatureManager> creatureManager;
    std::unique_ptr<TileRegistry> tileRegistry;
    std::unique_ptr<TileInstanceManager> tileInstanceManager;

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
    bool IsPositionEmpty(const Vec3 &pos) const;
    bool IsThereCreatureAt(const Vec3 &pos) const;
    bool IsPositionWalkable(const Vec3 &pos) const;
    std::list<Vec3> GetPath(const Vec3 &start, const Vec3 &end) const;

    const Vec2& GetTileSprite(const Vec3 &pos) const;
    const Color& GetTileColor(const Vec3 &pos) const;
    TileType* GetTypeForTileAt(const Vec3 &pos) const;
    std::string GetTypeIDForTileAt(const Vec3 &pos) const;
    std::string GetTypeIDForCreatureAt(const Vec3 &pos) const;

    void LoadData();
    void Update();
    void Generate();
    void GenerateTestBiome();
};
