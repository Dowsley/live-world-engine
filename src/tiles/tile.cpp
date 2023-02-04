#include "tile.h"

TileType::TileType(std::string name, unsigned short maxHealth)
{
    this->name = name;
    this->maxHealth = maxHealth;
}

TileType *TileType::AddDefaultSprite(olc::vi2d newDefaultSprite)
{
    this->defaultSprites.push_back(newDefaultSprite);
    return this;
}
TileType *TileType::AddDefaultForeColor(int r, int g, int b)
{
    this->defaultForeColors.push_back(olc::Pixel(r,g,b));
    return this;
}
TileType *TileType::AddDefaultBackColor(int r, int g, int b)
{
    this->defaultBackColors.push_back(olc::Pixel(r,g,b));
    return this;
}
TileType *TileType::SetSurface()
{
    this->isSurface = true;
    return this;
}

std::string TileType::GetName() { return name; }
unsigned short TileType::GetMaxHealth() { return maxHealth; }

olc::vi2d TileType::GetDefaultSprite(int index) { return defaultSprites[index]; }
olc::Pixel TileType::GetDefaultForeColor(int index) { return defaultForeColors[index]; }
olc::Pixel TileType::GetDefaultBackColor(int index) { return defaultBackColors[index]; }

int TileType::GetRandomDefaultSpriteIndex() { return rand() % defaultSprites.size(); }
int TileType::GetRandomDefaultForeColorIndex() { return rand() % defaultForeColors.size(); }
int TileType::GetRandomDefaultBackColorIndex() { return rand() % defaultBackColors.size(); }

TileMetadata::TileMetadata(Tile *parent, Organism *organism)
{
    this->parent = parent;
    this->health = parent->type->GetMaxHealth();
    this->organism = organism;
}

void TileMetadata::SetOrganism(Organism *organism)
{
    this->organism = organism;
}