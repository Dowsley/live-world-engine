#include "../core/world.h"
#include "../utils/geometry.h"

#include "manager.h"
#include "tile.h"

TileInstanceManager::TileInstanceManager(World *worldRef) : worldRef(worldRef) {}
TileInstanceManager::~TileInstanceManager()
{
    for(auto & pair : tileInstances) {
        delete pair.second;
    }
}

TileInstance* TileInstanceManager::GetInstanceAt(const Vec3 &pos) const
{
    int index = GeometryUtils::Flatten3DCoords(pos, worldRef->GetDimensions());
    if(tileInstances.find(index) != tileInstances.end()) {
        return tileInstances.at(index);
    }
    return nullptr;
}

TileInstance* TileInstanceManager::InstanceTile(const Tile *tile, const Vec3 &pos)
{
    // TODO: Create metadata. Implement interaction first.
    int index = GeometryUtils::Flatten3DCoords(pos, worldRef->GetDimensions());

    // If an instance already exists at that position, throw an error.
    if (tileInstances.find(index) != tileInstances.end()) {
        throw std::runtime_error("Tile already instantiated at position " + pos.ToString());
    }

    TileInstance *instance = new TileInstance(tile);
    tileInstances[index] = instance;
    return instance;
}

void TileInstanceManager::RemoveInstanceAt(const Vec3 &pos)
{
    int index = GeometryUtils::Flatten3DCoords(pos, worldRef->GetDimensions());
    if(tileInstances.find(index) != tileInstances.end()) {
        delete tileInstances[index];
        tileInstances.erase(index);
    }
}

void TileInstanceManager::TraverseInstances(std::function<void(TileInstance*)> callback)
{
    for(auto & pair : tileInstances) {
        callback(pair.second);
    }
}

void TileInstanceManager::UpdateInstances()
{
    for(auto & pair : tileInstances) {
        pair.second->Update();
    }
}

int TileInstanceManager::GetTotalInstanceCount() const
{
    return tileInstances.size();
}

void TileInstanceManager::ClearInstances()
{
    // TODO Make sure there will be no dangling references of creatures outside.
    tileInstances.clear();
}

const Vec2& TileInstanceManager::GetSprite(const Tile *tile) const
{
    // TODO Metadata check
    return tile->type->GetSpritePos(tile->spritePosVariantIndex);
}
const Color& TileInstanceManager::GetColor(const Tile *tile) const
{
    // TODO Metadata check
    return tile->type->GetSpriteColor(tile->spriteColorVariantIndex);
}
