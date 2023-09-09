#include "creature.h"

/* ---- CREATURE TYPE ---- */
const std::string& CreatureType::GetId() const { return id; }

const std::string& CreatureType::GetDescription() const { return description; }
const std::string& CreatureType::GetName() const { return name; }
const Vec2& CreatureType::GetSpritePos() const { return spritePos; }
const Color& CreatureType::GetSpriteColor() const { return spriteColor; }
int CreatureType::GetSpawnChance() const { return spawnChance; }

CreatureType* CreatureType::SetId(const std::string &id) { 
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


// Creature CreatureType::InstanceCreature() const
// {
//     return Creature(this);
// }

/* ---- CREATURE ---- */
Creature::Creature(CreatureType *type, Vec3 pos)
    : type(type), pos(pos) {};

bool Creature::Update()
{
    return false;
}
CreatureType* Creature::GetType() const { return type; }
const Vec3& Creature::GetPosition() const { return pos; }
void Creature::SetPosition(const Vec3 &pos) { this->pos = pos; }
