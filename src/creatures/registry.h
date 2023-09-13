#pragma once

#include "../core/base/registry.h"
#include "creature.h"
#include "loader.h"

class CreatureRegistry : public BaseRegistry<CreatureType, CreatureLoader> {
public:
    using BaseRegistry::BaseRegistry; // Inherit constructors

protected:
    std::vector<CreatureType*> _loadSpecific() override;
};
