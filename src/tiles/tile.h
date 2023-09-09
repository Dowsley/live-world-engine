#pragma once

#include <string>
#include <vector>
#include <random>

#include "../structures/color.h"
#include "../structures/vec2.h"

class TileType;
class Tile;
class TileMetadata;

class TileType {
private:
    std::string name;
    unsigned short maxHealth;

    std::vector<Vec2> defaultSprites;
    std::vector<Color> defaultForeColors;
    std::vector<Color> defaultBackColors;

public:
    static TileType *UNINITIALIZED;
    bool isSurface = false;
    TileType(std::string name, unsigned short maxHealth);

    TileType *AddDefaultSprite(const Vec2 &newDefaultSprite);
    TileType *AddDefaultForeColor(int r, int g, int b);
    TileType *AddDefaultBackColor(int r, int g, int b);
    TileType *SetSurface();

    std::string GetName() const;
    unsigned short GetMaxHealth() const;

    const Vec2& GetDefaultSprite(int index) const;
    Color GetDefaultForeColor(int index) const;
    Color GetDefaultBackColor(int index) const;

    int GetRandomDefaultSpriteIndex() const;
    int GetRandomDefaultForeColorIndex() const;
    int GetRandomDefaultBackColorIndex() const;
};

class Tile {
public:
    TileType *type = nullptr;
    TileMetadata *metadata = nullptr;

    unsigned char defaultSpriteIndex = 0;
    unsigned char defaultForeColorIndex = 0;
    unsigned char defaultBackColorIndex = 0;
};


class TileMetadata {
public:
    Tile *parent;
    unsigned short health;
    
    TileMetadata(Tile *parent);
};
