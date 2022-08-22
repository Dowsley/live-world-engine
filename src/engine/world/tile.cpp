#include "../graphics/olcPixelGameEngine.h"
#include <string>
#include <vector>
#include <random>

class TileType;
class Tile;
class TileMetadata;

class TileType {
private:
    std::string name;
    unsigned short maxHealth;

    std::vector<olc::vi2d> defaultSprites;
    std::vector<olc::Pixel> defaultForeColors;
    std::vector<olc::Pixel> defaultBackColors;

public:
    static TileType *UNINITIALIZED;
    TileType(std::string name, unsigned short maxHealth)
    {
        this->name = name;
        this->maxHealth = maxHealth;
    };

    TileType *AddDefaultSprite(olc::vi2d newDefaultSprite)
    {
        this->defaultSprites.push_back(newDefaultSprite);
        return this;
    };
    TileType *AddDefaultForeColor(int newDefaultForeColorHex)
    {
        this->defaultForeColors.push_back(olc::Pixel(newDefaultForeColorHex));
        return this;
    };
    TileType *AddDefaultBackColor(int newDefaultBackColorHex)
    {
        this->defaultBackColors.push_back(olc::Pixel(newDefaultBackColorHex));
        return this;
    };

    std::string GetName() { return name; };
    unsigned short GetMaxHealth() { return maxHealth; };

	olc::vi2d GetDefaultSprite(int index) { return defaultSprites[index]; };
	olc::Pixel GetDefaultForeColor(int index) { return defaultForeColors[index]; };
	olc::Pixel GetDefaultBackColor(int index) { return defaultBackColors[index]; };

    int GetRandomDefaultSpriteIndex() { return rand() % defaultSprites.size(); };
    int GetRandomDefaultForeColorIndex() { return rand() % defaultForeColors.size(); };
    int GetRandomDefaultBackColorIndex() { return rand() % defaultBackColors.size(); };
};

TileType *TileType::UNINITIALIZED = new TileType("uninitialized", 0);

class Tile {
public:
    TileType *type = TileType::UNINITIALIZED;
    TileMetadata *metadata = nullptr;

    unsigned char defaultSpriteIndex = 0;
    unsigned char defaultForeColorIndex = 0;
    unsigned char defaultBackColorIndex = 0;

    // Tile(TileType *type, unsigned char defaultSpriteIndex, unsigned char defaultForeColorIndex, unsigned char defaultBackColorIndex)
    // : type(type),
    // defaultSpriteIndex(defaultSpriteIndex),
    // defaultForeColorIndex(defaultForeColorIndex),
    // defaultBackColorIndex(defaultBackColorIndex)
    // {};
};


class TileMetadata {
private:
    Tile *parent;
    unsigned short health;
    bool isSlope = false;
    // TODO Entity entity;
    // TODO bool isOccluded = true;

public:
    TileMetadata(Tile *parent)
    {
        this->parent = parent;
        this->health = parent->type->GetMaxHealth();
    }
    TileMetadata(Tile *parent, bool isSlope)
    {
        this->parent = parent;
        this->health = parent->type->GetMaxHealth();
        this->isSlope = isSlope;
    }
};
