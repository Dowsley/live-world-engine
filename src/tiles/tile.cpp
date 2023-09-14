#include "tile.h"

/* Tile Type */

const std::string& TileType::GetID() const { return id; }
const std::string& TileType::GetDescription() const { return description; }
const std::string& TileType::GetName() const { return name; }
const std::vector<SpriteVariant>& TileType::GetSpriteVariants() const { return spriteVariants; }
unsigned int TileType::GetMaxHealth() const { return maxHealth; }
bool TileType::GetIsSolid() const { return isSolid; }


const SpriteVariant& TileType::GetSprite(int index) const { return spriteVariants[index]; }
int TileType::GetRandomSpriteIndex() const { return rand() % spriteVariants.size(); } // TODO: Better randomize this with a random util lib


TileType* TileType::SetID(const std::string &id) { this->id = id; return this; }
TileType* TileType::SetDescription(const std::string &description) { this->description = description; return this; }
TileType* TileType::SetName(const std::string &name) { this->name = name; return this; }
TileType* TileType::AddSpriteVariant(const SpriteVariant &spriteVariant) { this->spriteVariants.push_back(spriteVariant); return this; }
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
