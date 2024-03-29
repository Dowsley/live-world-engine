#include "creature.h"

/* ---- CREATURE TYPE ---- */
const std::string& CreatureType::GetID() const { return id; }

const std::string& CreatureType::GetDescription() const { return description; }
const std::string& CreatureType::GetName() const { return name; }
const Vec2& CreatureType::GetSpritePos() const { return spritePos; }
const Color& CreatureType::GetSpriteColor() const { return spriteColor; }
int CreatureType::GetSpawnChance() const { return spawnChance; }

CreatureType* CreatureType::SetID(const std::string &id) { 
    this->id = id;
    return this;
}

CreatureType* CreatureType::SetDescription(const std::string &descriptionVal) {
    description = descriptionVal;
    return this;
}

CreatureType* CreatureType::SetName(const std::string &name) { 
    this->name = name;
    return this;
}

CreatureType* CreatureType::SetSpritePos(const Vec2 &pos) { 
    this->spritePos = pos;
    return this;
}

CreatureType* CreatureType::SetSpriteColor(const Color &color) { 
    this->spriteColor = color;
    return this;
}

CreatureType* CreatureType::SetSpawnChance(int spawnChance) { 
    this->spawnChance = spawnChance;
    return this;
}

/* ---- CREATURE ---- */
Creature::Creature(const CreatureType &type, Vec3 pos)
    : type(type), pos(pos) {};

std::optional<Vec3> Creature::Update()
{
    
    return std::nullopt;
}
const CreatureType& Creature::GetType() const { return type; }
const Vec3& Creature::GetPosition() const { return pos; }
void Creature::SetPosition(Vec3 pos) { this->pos = pos; }
