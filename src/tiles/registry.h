#pragma once

#include "../core/base/registry.h"
#include "tile.h"
#include "loader.h"

class TileRegistry : public BaseRegistry<TileType, TileLoader> {
public:
    using BaseRegistry::BaseRegistry; // Inherit constructors

protected:
    std::vector<TileType*> _loadSpecific() override;
};
