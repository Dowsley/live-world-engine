#include "manager.h"

#include <utility>

#include "../core/world.h"
#include "geometry.h"

CreatureManager::CreatureManager(World *world) : ManagerBase<Creature>(world) {
    registry.Initialize();
}

CreatureManager::~CreatureManager() {
    ClearItems();
}

Creature* CreatureManager::GetItemAt(const Vec3 &pos) const {
    int index = GeometryUtils::Flatten3DCoords(pos, worldRef->GetDimensions());
    auto it = items.find(index);
    return (it != items.end()) ? it->second : nullptr;
}

void CreatureManager::TraverseItems(std::function<void(Creature*)> callback) {
    for (auto& item : items) {
        callback(item.second);
    }
}

int CreatureManager::GetTotalItemCount() const {
    return items.size();
}

void CreatureManager::ClearItems() {
    for (auto& item : items) {
        delete item.second;
        item.second = nullptr;
    }
    items.clear();
}

const CreatureType* CreatureManager::GetTypeById(const std::string &id) const
{
    return registry.GetTypeById(id);
}

Creature* CreatureManager::InstanceCreature(const std::string &typeID, const Vec3 &pos)
{
    int index = GeometryUtils::Flatten3DCoords(pos, worldRef->GetDimensions());

    // If creature already exists at that position
    if (items.find(index) != items.end()) {
        return nullptr;
    }

    CreatureType *type = registry.GetTypeById(typeID);
    if (type == nullptr) {
        throw std::runtime_error("Type not implemented: " + typeID);
    }

    auto *newCreature = new Creature(*type, pos);
    items[index] = newCreature;

    return newCreature;
}

void CreatureManager::RemoveCreatureAt(const Vec3 &pos)
{
    int index = GeometryUtils::Flatten3DCoords(pos, worldRef->GetDimensions());
    if(items.find(index) != items.end()) {
        delete items[index]; // Delete the creature from the heap
        items.erase(index);  // Remove the entry from the map
    }
}

void CreatureManager::UpdateCreatures(const World &world)
{
    std::unordered_map<int, Creature*> updatedItems;

    for(auto& pair : items) {
        Creature *creature = pair.second;
        std::optional<Vec3> posOpt = creature->Update(world);

        if (!posOpt.has_value()) {
            updatedItems[pair.first] = creature;  // No movement, keep creature in its current position
            continue;
        }

        Vec3 newPos = posOpt.value();
        if (!worldRef->IsInBounds(newPos) || !worldRef->IsPositionWalkable(newPos)) {
            updatedItems[pair.first] = creature;  // Invalid move, keep creature in its current position
            continue;
        }
        int newIndex = GeometryUtils::Flatten3DCoords(newPos, worldRef->GetDimensions());
        if (updatedItems.find(newIndex) != updatedItems.end()) {
            updatedItems[pair.first] = creature;  // Position already taken in this update cycle, keep creature in its current position
            continue;
        }

        creature->SetPosition(newPos);
        updatedItems[newIndex] = creature;
    }

    items.swap(updatedItems);
}

void CreatureManager::ClearCreatures() {
    ClearItems();
}

std::vector<const CreatureType*> CreatureManager::GetAllTypes() const
{
    return registry.GetAllTypes();
}
