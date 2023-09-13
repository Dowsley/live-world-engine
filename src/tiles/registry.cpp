#include "registry.h"

TileRegistry::TileRegistry(const std::string &path)
: loader(path) {
    _loadTiles();
}

TileRegistry::~TileRegistry()
{
    for (auto & tile : tileTypes) {
        delete tile.second;
    }
}

TileType* TileRegistry::GetTypeById(const std::string &id) const
{
    auto it = tileTypes.find(id);
    if (it != tileTypes.end()) {
        return it->second;
    }
    return nullptr;
}

void TileRegistry::ReloadTiles()
{
    tileTypes.clear();
    _loadTiles();
}

void TileRegistry::_loadTiles()
{
    for (const auto & type : loader.LoadAll()) {
        tileTypes[type->GetID()] = type;
    }
}
