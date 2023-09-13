#include "manager.h"
#include "../core/world.h"

CreatureManager::CreatureManager(World *world) : ManagerBase<Creature>(world) {
    registry.Initialize();
}

CreatureManager::~CreatureManager() {
    ClearItems();
}

const CreatureType* CreatureManager::GetTypeById(const std::string &id) const {
    return registry.GetTypeById(id);
}

Creature* CreatureManager::InstanceCreature(const std::string &typeID, const Vec3 &pos) {
    int index = GeometryUtils::Flatten3DCoords(pos, worldRef->GetDimensions());

    // If creature already exists at that position
    if (items.find(index) != items.end()) {
        return nullptr;
    }

    CreatureType *type = registry.GetTypeById(typeID);
    if (type == nullptr) {
        throw std::runtime_error("Type not implemented: " + typeID);
    }

    Creature* newCreature = new Creature(type, pos);
    items[index] = newCreature;
    return newCreature;
}

void CreatureManager::RemoveCreatureAt(const Vec3 &pos) {
    int index = GeometryUtils::Flatten3DCoords(pos, worldRef->GetDimensions());
    if(items.find(index) != items.end()) {
        delete items[index]; // Delete the creature from the heap
        items.erase(index);  // Remove the entry from the map
    }
}

void CreatureManager::UpdateCreatures() {
    for(auto & pair : items) {
        pair.second->Update();
    }
}

void CreatureManager::TraverseCreatures(std::function<void(Creature*)> callback) {
    TraverseItems(callback);
}

void CreatureManager::ClearCreatures() {
    ClearItems();
}