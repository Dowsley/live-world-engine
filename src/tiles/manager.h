#pragma once

#include "../core/base/manager.h"
#include "tile.h"

#include <unordered_map>

class TileInstanceManager : public ManagerBase<TileInstance> {
private:
    std::unordered_map<int, TileInstance*> items;

public:
    explicit TileInstanceManager(World *world);
    ~TileInstanceManager() override;

    TileInstance* GetItemAt(const Vec3 &pos) const override;
    void TraverseItems(std::function<void(TileInstance*)> callback) override;
    int GetTotalItemCount() const override;
    void ClearItems() override;

    TileInstance* InstanceTile(const Tile *tile, const Vec3 &pos);
    void RemoveInstanceAt(const Vec3 &pos);
    void UpdateInstances();
    void ClearInstances();

    const SpriteVariant& GetSprite(const Tile *tile) const;
};
