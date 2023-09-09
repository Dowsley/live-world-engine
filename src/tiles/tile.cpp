#include "tile.h"

TileType::TileType(std::string name, unsigned short maxHealth)
{
    this->name = name;
    this->maxHealth = maxHealth;
}

TileType *TileType::AddDefaultSprite(const Vec2 &newDefaultSprite)
{
    this->defaultSprites.push_back(newDefaultSprite);
    return this;
}
TileType *TileType::AddDefaultForeColor(int r, int g, int b)
{
    this->defaultForeColors.push_back(Color(r,g,b));
    return this;
}
TileType *TileType::AddDefaultBackColor(int r, int g, int b)
{
    this->defaultBackColors.push_back(Color(r,g,b));
    return this;
}
TileType *TileType::SetSurface()
{
    this->isSurface = true;
    return this;
}

std::string TileType::GetName() const { return name; }
unsigned short TileType::GetMaxHealth() const { return maxHealth; }

const Vec2& TileType::GetDefaultSprite(int index) const { return defaultSprites[index]; }
const Color& TileType::GetDefaultForeColor(int index) const { return defaultForeColors[index]; }
const Color& TileType::GetDefaultBackColor(int index) const { return defaultBackColors[index]; }

int TileType::GetRandomDefaultSpriteIndex() const { return rand() % defaultSprites.size(); }
int TileType::GetRandomDefaultForeColorIndex() const { return rand() % defaultForeColors.size(); }
int TileType::GetRandomDefaultBackColorIndex() const { return rand() % defaultBackColors.size(); }

TileMetadata::TileMetadata(Tile *parent)
{
    this->parent = parent;
    this->health = parent->type->GetMaxHealth();
}
