#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "../lib/tinyxml2.h"
#include "creature.h"
#include "loader.h"

class CreatureRegistry {
public:
    explicit CreatureRegistry(const std::string &path);
    ~CreatureRegistry();

    CreatureType* GetTypeById(const std::string &name) const;
    void ReloadCreatures(); // Use this to reload creatures if the files are updated.

private:
    void _loadCreatures();

    CreatureLoader loader;
    std::unordered_map<std::string, CreatureType*> creatureTypes;
};
