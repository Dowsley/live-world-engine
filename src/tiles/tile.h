#pragma once

#include <string>
#include <vector>
#include <random>

#include "../structures/color.h"
#include "../structures/vec2.h"

class TileType;
struct Tile;
class TileInstance;

class TileType {
private:
private:
    std::string id;
    std::string name;
    std::string description;
    unsigned int maxHealth;
    bool isSolid = false;
    
    std::vector<Vec2> spritePosVariants;
    std::vector<Color> spriteColorVariants;

public:
    static TileType *UNINITIALIZED;

    const std::string& GetID() const;
    const std::string& GetDescription() const;
    const std::string& GetName() const;
    const std::vector<Vec2>& GetSpritePosVariants() const;
    const std::vector<Color>& GetSpriteColorVariants() const;
    unsigned int GetMaxHealth() const;
    bool GetIsSolid() const;

    const Vec2& GetSpritePos(int index) const;
    const Color& GetSpriteColor(int index) const;
    int GetRandomSpritePosIndex() const;
    int GetRandomSpriteColorIndex() const;

    TileType* SetID(const std::string &id);
    TileType* SetDescription(const std::string &description);
    TileType* SetName(const std::string &name);
    TileType* AddSpritePosVariant(const Vec2 &pos);
    TileType* AddSpriteColorVariant(const Color &color);
    TileType* SetMaxHealth(unsigned int maxHealth);
    TileType* SetIsSolid();
};

struct Tile {
    TileType *type = nullptr;
    unsigned char spritePosVariantIndex = 0;
    unsigned char spriteColorVariantIndex = 0;
};


class TileInstance {
public:
    const Tile *parent;
    unsigned short health;
    
    TileInstance(const Tile *parent);
    bool Update();
};
