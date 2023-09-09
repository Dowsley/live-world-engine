#include <filesystem>

#include "registry.h"
#include "creature.h"

CreatureRegistry::CreatureRegistry(const std::string& path)
: loader(path) {
    LoadCreatures();
}

CreatureRegistry::~CreatureRegistry()
{
    for (auto & creature : creatureTypes) {
        delete creature.second;
    }
}

CreatureType* CreatureRegistry::GetTypeById(const std::string &id) const
{
    auto it = creatureTypes.find(id);
    if (it != creatureTypes.end()) {
        return it->second;
    }
    return nullptr;
}

void CreatureRegistry::ReloadCreatures()
{
    creatureTypes.clear();
    LoadCreatures();
}

void CreatureRegistry::LoadCreatures()
{
    for (const auto & type : loader.LoadAllCreatures()) {
        creatureTypes[type->GetId()] = type;
    }
}
