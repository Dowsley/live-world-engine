#include "registry.h"

std::vector<TileType*> TileRegistry::_loadSpecific() {
    return loader.LoadAll();
}
