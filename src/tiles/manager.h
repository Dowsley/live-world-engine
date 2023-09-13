#pragma once

#include <unordered_map>
#include <functional>

#include "tile.h"
#include "registry.h"
#include "../structures/vec3.h"
#include "../core/settings.h"

class World;

class TileInstanceManager {
private:
    World *worldRef = nullptr;
    std::unordered_map<int, TileInstance*> tileInstances;

public:
    TileInstanceManager(World *world);
    ~TileInstanceManager();

    TileInstance* GetInstanceAt(const Vec3 &pos) const;
    TileInstance* InstanceTile(const Tile *tile, const Vec3 &pos);
    void RemoveInstanceAt(const Vec3 &pos);
    void UpdateInstances();
    void TraverseInstances(std::function<void(TileInstance*)> callback);
    int GetTotalInstanceCount() const;
    void ClearInstances();

    const Vec2& GetSprite(const Tile *tile) const;
    const Color& GetColor(const Tile *tile) const;
};
