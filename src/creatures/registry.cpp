#include "registry.h"

std::vector<CreatureType*> CreatureRegistry::_loadSpecific() {
    return loader.LoadAll();
}
