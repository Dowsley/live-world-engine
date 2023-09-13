#pragma once

#include <string>

#include "../core/base/loader.h"
#include "tile.h"

class TileLoader : public BaseLoader<TileType> {
public:
    explicit TileLoader(const std::string &path) : BaseLoader(path) {}

protected:
    TileType* _loadSpecific(const std::string &tileFile) override;
};
