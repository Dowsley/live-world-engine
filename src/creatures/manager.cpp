#include "../core/world.h"
#include "../utils/geometry.h"
#include "manager.h"
#include "creature.h"

CreatureManager::CreatureManager(World *worldRef) : worldRef(worldRef)
{
    registry.Initialize();
}

CreatureManager::~CreatureManager()
{
    for(auto & pair : creatureMap) {
        delete pair.second;
    }
}

const CreatureType* CreatureManager::GetTypeById(const std::string &id) const
{
    return registry.GetTypeById(id);
}


Creature* CreatureManager::GetCreatureAt(const Vec3 &pos) const
{
    int index = GeometryUtils::Flatten3DCoords(pos, worldRef->GetDimensions());
    if(creatureMap.find(index) != creatureMap.end()) {
        return creatureMap.at(index);
    }
    return nullptr;
}

Creature* CreatureManager::InstanceCreature(const std::string &typeID, const Vec3 &pos)
{
    int index = GeometryUtils::Flatten3DCoords(pos, worldRef->GetDimensions());
    // If creature already exists at that position
    if (creatureMap.find(index) != creatureMap.end()) {
        return nullptr;
    }

    CreatureType *type = registry.GetTypeById(typeID);
    if (type == nullptr) {
        throw std::runtime_error("Type not implemented: " + typeID);
    }

    Creature* newCreature = new Creature(type, pos);
    creatureMap[index] = newCreature;
    return newCreature;
}

void CreatureManager::RemoveCreatureAt(const Vec3 &pos)
{
    int index = GeometryUtils::Flatten3DCoords(pos, worldRef->GetDimensions());
    if(creatureMap.find(index) != creatureMap.end()) {
        delete creatureMap[index]; // Delete the creature from the heap
        creatureMap.erase(index);  // Remove the entry from the map
    }
}

void CreatureManager::TraverseCreatures(std::function<void(Creature*)> callback)
{
    for(auto & pair : creatureMap) {
        callback(pair.second);
    }
}

void CreatureManager::UpdateCreatures()
{
    for(auto & pair : creatureMap) {
        pair.second->Update();
    }
}

int CreatureManager::GetTotalCreatureCount() const
{
    return creatureMap.size();
}

void CreatureManager::ClearCreatures()
{
    // TODO Make sure there will be no dangling references of creatures outside.
    creatureMap.clear();
}