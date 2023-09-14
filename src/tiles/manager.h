#pragma once

#include "../core/base/manager.h"
#include "tile.h"

class TileInstanceManager : public ManagerBase<TileInstance> {
public:
    TileInstanceManager(World *world);
    ~TileInstanceManager();

    TileInstance* InstanceTile(const Tile *tile, const Vec3 &pos);
    void RemoveInstanceAt(const Vec3 &pos);
    void UpdateInstances();
    void TraverseInstances(std::function<void(TileInstance*)> callback);
    void ClearInstances();

    const SpriteVariant& GetSprite(const Tile *tile) const;
};
