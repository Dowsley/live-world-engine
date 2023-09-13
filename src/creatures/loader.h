#pragma once

#include <string>

#include "../core/base_loader.h"
#include "creature.h"

class CreatureLoader : public BaseLoader<CreatureType> {
public:
    explicit CreatureLoader(const std::string &path) : BaseLoader(path) {}

protected:
    CreatureType* _loadSpecific(const std::string &creatureFile) override;
};
