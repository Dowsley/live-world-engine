#pragma once

#include "../core/base/manager.h"
#include "../core/settings.h"

#include "creature.h"
#include "registry.h"

class CreatureManager : public ManagerBase<Creature> {
private:
    CreatureRegistry registry = CreatureRegistry(Settings::CREATURE_REGISTRY_PATH);
public:
    explicit CreatureManager(World *world);
    ~CreatureManager() override;

    const CreatureType* GetTypeById(const std::string &id) const;
    Creature* InstanceCreature(const std::string &typeID, const Vec3 &pos);
    void RemoveCreatureAt(const Vec3 &pos);
    void UpdateCreatures();
    void TraverseCreatures(std::function<void(Creature*)> callback);
    void ClearCreatures();
    std::vector<const CreatureType*> GetAllTypes() const;
};
