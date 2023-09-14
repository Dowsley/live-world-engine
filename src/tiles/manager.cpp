#include "manager.h"
#include "../core/world.h"

TileInstanceManager::TileInstanceManager(World *world) : ManagerBase<TileInstance>(world) {}

TileInstanceManager::~TileInstanceManager() {
    ClearItems();
}

TileInstance* TileInstanceManager::InstanceTile(const Tile *tile, const Vec3 &pos) {
    int index = GeometryUtils::Flatten3DCoords(pos, worldRef->GetDimensions());

    // If an instance already exists at that position, throw an error.
    if (items.find(index) != items.end()) {
        throw std::runtime_error("Tile already instantiated at position " + pos.ToString());
    }

    TileInstance *instance = new TileInstance(tile);
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

void TileInstanceManager::TraverseInstances(std::function<void(TileInstance*)> callback) {
    TraverseItems(callback);
}

void TileInstanceManager::ClearInstances() {
    ClearItems();
}

const SpriteVariant& TileInstanceManager::GetSprite(const Tile *tile) const {
    // TODO Metadata check
    return tile->type->GetSprite(tile->spriteVariantIndex);
}
