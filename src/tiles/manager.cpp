#include "manager.h"

#include "../core/world.h"
#include "geometry.h"

TileInstanceManager::TileInstanceManager(World *world) : ManagerBase<TileInstance>(world) {}

TileInstanceManager::~TileInstanceManager() {
    ClearItems();
}

TileInstance* TileInstanceManager::GetItemAt(const Vec3 &pos) const {
    int index = GeometryUtils::Flatten3DCoords(pos, worldRef->GetDimensions());
    auto it = items.find(index);
    return (it != items.end()) ? it->second : nullptr;
}

void TileInstanceManager::TraverseItems(std::function<void(TileInstance*)> callback) {
    for (auto& item : items) {
        callback(item.second);
    }
}

int TileInstanceManager::GetTotalItemCount() const {
    return items.size();
}

void TileInstanceManager::ClearItems() {
    for (auto& item : items) {
        delete item.second;
        item.second = nullptr;
    }
    items.clear();
}

TileInstance* TileInstanceManager::InstanceTile(const Tile *tile, const Vec3 &pos) {
    int index = GeometryUtils::Flatten3DCoords(pos, worldRef->GetDimensions());
    if (items.find(index) != items.end()) {
        throw std::runtime_error("Tile already instantiated at position " + pos.ToString());
    }
    auto *instance = new TileInstance(tile);
    items[index] = instance;
    return instance;
}

void TileInstanceManager::RemoveInstanceAt(const Vec3 &pos) {
    int index = GeometryUtils::Flatten3DCoords(pos, worldRef->GetDimensions());
    if(items.find(index) != items.end()) {
        delete items[index];
        items.erase(index);
    }
}

void TileInstanceManager::UpdateInstances() {
    for(auto & pair : items) {
        pair.second->Update();
    }
}

void TileInstanceManager::ClearInstances() {
    ClearItems();
}

const SpriteVariant& TileInstanceManager::GetSprite(const Tile *tile) const {
    // TODO Metadata check
    return tile->type->GetSprite(tile->spriteVariantIndex);
}
