#include "tile.h"

/* Tile Type */

const std::string& TileType::GetID() const { return id; }
const std::string& TileType::GetDescription() const { return description; }
const std::string& TileType::GetName() const { return name; }
const std::vector<Vec2>& TileType::GetSpritePosVariants() const { return spritePosVariants; }
const std::vector<Color>& TileType::GetSpriteColorVariants() const { return spriteColorVariants; }
unsigned int TileType::GetMaxHealth() const { return maxHealth; }
bool TileType::GetIsSolid() const { return isSolid; }


const Vec2& TileType::GetSpritePos(int index) const { return spritePosVariants[index]; }
const Color& TileType::GetSpriteColor(int index) const { return spriteColorVariants[index]; }
int TileType::GetRandomSpritePosIndex() const { return rand() % spritePosVariants.size(); } // TODO: Better randomize this with a random util lib
int TileType::GetRandomSpriteColorIndex() const { return rand() % spriteColorVariants.size(); }


TileType* TileType::SetID(const std::string &id) { this->id = id; return this; }
TileType* TileType::SetDescription(const std::string &description) { this->description = description; return this; }
TileType* TileType::SetName(const std::string &name) { this->name = name; return this; }
TileType* TileType::AddSpritePosVariant(const Vec2 &pos) { this->spritePosVariants.push_back(pos); return this; }
TileType* TileType::AddSpriteColorVariant(const Color &color) { this->spriteColorVariants.push_back(color); return this; }
TileType* TileType::SetMaxHealth(unsigned int maxHealth) { this->maxHealth = maxHealth; return this; }
TileType* TileType::SetIsSolid() { this->isSolid = true; return this; }

/* Tile Instance */

TileInstance::TileInstance(const Tile *parent)
{
    this->parent = parent;
    this->health = parent->type->GetMaxHealth();
}

bool TileInstance::Update()
{
    return false;
}
