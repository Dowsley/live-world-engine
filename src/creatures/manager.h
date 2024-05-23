#pragma once

#include "../core/base/manager.h"
#include "../core/settings.h"
#include "creature.h"
#include "registry.h"
#include <unordered_map>

class CreatureManager : public ManagerBase<Creature> {
private:
    CreatureRegistry registry = CreatureRegistry(Settings::CREATURE_REGISTRY_PATH);
    std::unordered_map<int, Creature*> items;

public:
    explicit CreatureManager(World *world);
    ~CreatureManager() override;

    Creature* GetItemAt(const Vec3 &pos) const override;
    void TraverseItems(std::function<void(Creature*)> callback) override;
    [[nodiscard]] int GetTotalItemCount() const override;
    void ClearItems() override;

    const CreatureType* GetTypeById(const std::string &id) const;
    Creature* InstanceCreature(const std::string &typeID, const Vec3 &pos);
    void RemoveCreatureAt(const Vec3 &pos);
    void UpdateCreatures(const World &world);
    void ClearCreatures();
    std::vector<const CreatureType*> GetAllTypes() const;
};
