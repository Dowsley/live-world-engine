#pragma once

#include <string>
#include <vector>
#include <random>

#include "../structures/color.h"
#include "../structures/vec2.h"

class TileType;
struct Tile;
class TileInstance;

struct SpriteVariant {
    Vec2 position;
    Color color;

    SpriteVariant(const Vec2& pos, const Color& col)
        : position(pos), color(col) {}
};

class TileType {
private:
private:
    std::string id;
    std::string name;
    std::string description;
    unsigned int maxHealth;
    bool isSolid = false;

    std::vector<SpriteVariant> spriteVariants;

public:
    static TileType *UNINITIALIZED;

    const std::string& GetID() const;
    const std::string& GetDescription() const;
    const std::string& GetName() const;
    const std::vector<SpriteVariant>& GetSpriteVariants() const;
    unsigned int GetMaxHealth() const;
    bool GetIsSolid() const;

    const SpriteVariant& GetSprite(int index) const;
    int GetRandomSpriteIndex() const;

    TileType* SetID(const std::string &id);
    TileType* SetDescription(const std::string &description);
    TileType* SetName(const std::string &name);
    TileType* AddSpriteVariant(const SpriteVariant &spriteVariant);
    TileType* SetMaxHealth(unsigned int maxHealth);
    TileType* SetIsSolid();
};

struct Tile {
    TileType *type = nullptr;
    unsigned char spriteVariantIndex = 0;
};


class TileInstance {
public:
    const Tile *parent;
    unsigned short health;

    explicit TileInstance(const Tile *parent);
    bool Update();
};
