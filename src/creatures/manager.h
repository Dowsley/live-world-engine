#ifndef CREATURE_MANAGER_H
#define CREATURE_MANAGER_H

#include <unordered_map>
#include <functional>

#include "creature.h"
#include "registry.h"
#include "../structures/vec3.h"
#include "../core/settings.h"

class World;

class CreatureManager {
private:
    World *worldRef = nullptr;
    std::unordered_map<int, Creature*> creatureMap;

    CreatureRegistry registry = CreatureRegistry(Settings::CREATURE_REGISTRY_PATH);

public:
    CreatureManager(World *world);
    ~CreatureManager();

    const CreatureType* GetTypeById(const std::string &id) const;
    Creature* GetCreatureAt(Vec3 pos) const;
    bool InstanceCreature(const std::string &name, Vec3 pos);
    void RemoveCreatureAt(Vec3 pos);
    void UpdateEntities();
    void TraverseEntities(std::function<void(Creature*)> callback);
    int GetTotalCreatureCount();
};

#endif