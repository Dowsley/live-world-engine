#pragma once

#include <string>

#include "registry.h"
#include "creature.h"
#include "../lib/tinyxml2.h"

class CreatureLoader {
public:
    explicit CreatureLoader(const std::string &path);
    std::vector<CreatureType*> LoadAllCreatures();

private:
    CreatureType* _loadCreature(const std::string& creatureFile);
    std::string directoryPath;
};
