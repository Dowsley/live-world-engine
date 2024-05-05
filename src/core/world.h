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

    [[nodiscard]] std::tuple<Tile*, Creature*> _getTileAndCreature(const Vec3 &pos) const;
    [[nodiscard]] Tile* _getTile(const Vec3 &pos) const;
    void _setTile(const Vec3 &pos, TileType *type);
    void _swapTiles(Tile *tile1, Tile *tile2);

public:
    explicit World(Vec3 dimensions);
    ~World();

    [[nodiscard]] int GetHeight() const;
    [[nodiscard]] int GetWidth() const;
    [[nodiscard]] int GetDepth() const;
    [[nodiscard]] const Vec3& GetDimensions() const;
    [[nodiscard]] bool IsPositionEmpty(const Vec3 &pos) const;
    [[nodiscard]] bool IsThereCreatureAt(const Vec3 &pos) const;
    [[nodiscard]] bool IsPositionWalkable(const Vec3 &pos) const;
    [[nodiscard]] bool IsInBounds(const Vec3 &pos) const;
    [[nodiscard]] std::list<Vec3> GetPath(const Vec3 &start, const Vec3 &end) const;

    [[nodiscard]] const Vec2& GetTileSprite(const Vec3 &pos) const;
    [[nodiscard]] const Color& GetTileColor(const Vec3 &pos) const;
    [[nodiscard]] TileType* GetTypeForTileAt(const Vec3 &pos) const;
    [[nodiscard]] std::string GetTypeIDForTileAt(const Vec3 &pos) const;
    [[nodiscard]] std::string GetTypeIDForCreatureAt(const Vec3 &pos) const;

    void LoadData();
    void Update();
    void Generate();
    void GenerateTestBiome();
};
