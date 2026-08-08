#pragma once

#include "core/base/registry.h"
#include "creatures/creature.h"
#include "creatures/loader.h"

class CreatureRegistry : public BaseRegistry<CreatureType, CreatureLoader> {
public:
    using BaseRegistry::BaseRegistry; // Inherit constructors

protected:
    std::vector<CreatureType*> _loadSpecific() override;
};
