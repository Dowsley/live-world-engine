#include "registry.h"
#include "creature.h"

CreatureRegistry::CreatureRegistry(const std::string& path)
: loader(path) {
    _loadCreatures();
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
    _loadCreatures();
}

void CreatureRegistry::_loadCreatures()
{
    for (const auto & type : loader.LoadAll()) {
        creatureTypes[type->GetID()] = type;
    }
}
