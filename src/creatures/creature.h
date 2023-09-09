#ifndef CREATURE_H
#define CREATURE_H

#include <string>

#include "../structures/index.h"

//TODO: Make component-based creatures
class CreatureType {
public:
    const std::string& GetId() const;
    const std::string& GetDescription() const;
    const std::string& GetName() const;
    const Vec2 GetSpritePos() const;
    const Color& GetSpriteColor() const;
    int GetSpawnChance() const;

    CreatureType* SetId(const std::string &id);
    CreatureType* SetDescription(const std::string &description);
    CreatureType* SetName(const std::string &name);
    CreatureType* SetSpritePos(Vec2 pos);
    CreatureType* SetSpriteColor(Color color);
    CreatureType* SetSpawnChance(int chance);

private:
    std::string id;
    std::string name;
    std::string description;
    Vec2 spritePos;
    Color spriteColor;
    int spawnChance;
};

class Creature {
public:
    Creature(CreatureType *type, Vec3 pos);

    CreatureType* GetType() const;
    Vec3 GetPosition() const;
    void SetPosition(Vec3 pos);
    bool Update();
private:
    Vec3 pos;
    CreatureType *type;
};

#endif