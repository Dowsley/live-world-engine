#ifndef TILE_H
#define TILE_H

#include <string>
#include <vector>
#include <random>

#include "../graphics/olcPixelGameEngine.h"
#include "../organisms/organism.h"

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
    bool isSurface = false;
    TileType(std::string name, unsigned short maxHealth);

    TileType *AddDefaultSprite(olc::vi2d newDefaultSprite);
    TileType *AddDefaultForeColor(int r, int g, int b);
    TileType *AddDefaultBackColor(int r, int g, int b);
    TileType *SetSurface();

    std::string GetName();
    unsigned short GetMaxHealth();

	olc::vi2d GetDefaultSprite(int index);
	olc::Pixel GetDefaultForeColor(int index);
	olc::Pixel GetDefaultBackColor(int index);

    int GetRandomDefaultSpriteIndex();
    int GetRandomDefaultForeColorIndex();
    int GetRandomDefaultBackColorIndex();
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
    Organism *organism;
    
    TileMetadata(Tile *parent, Organism *organism);
    void SetOrganism(Organism *organism);
};

#endif