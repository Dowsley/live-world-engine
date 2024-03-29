#pragma once

#include <string>
#include <optional>

#include "../structures/index.h"

//TODO: Make component-based creatures
class CreatureType {
public:
    const std::string& GetID() const;
    const std::string& GetDescription() const;
    const std::string& GetName() const;
    const Vec2& GetSpritePos() const;
    const Color& GetSpriteColor() const;
    int GetSpawnChance() const;

    CreatureType* SetID(const std::string &id);
    CreatureType* SetDescription(const std::string &description);
    CreatureType* SetName(const std::string &name);
    CreatureType* SetSpritePos(const Vec2 &pos);
    CreatureType* SetSpriteColor(const Color &color);
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
private:
    const CreatureType &type;
    Vec3 pos;

public:
    Creature(const CreatureType &type, Vec3 pos);

    const CreatureType& GetType() const;
    const Vec3& GetPosition() const;
    void SetPosition(Vec3 pos);
    std::optional<Vec3> Update();
};
