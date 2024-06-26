#pragma once

#include <string>
#include <optional>

#include "../structures/index.h"

class World;

enum DietType {
    CARNIVORE,
    HERBIVORE
};

//TODO: Make component-based creatures
class CreatureType {
public:
    [[nodiscard]] const std::string& GetID() const;
    [[nodiscard]] const std::string& GetDescription() const;
    [[nodiscard]] const std::string& GetName() const;
    [[nodiscard]] const Vec2& GetSpritePos() const;
    [[nodiscard]] const Color& GetSpriteColor() const;
    [[nodiscard]] int GetSpawnChance() const;
    [[nodiscard]] DietType GetDietType() const;

    CreatureType* SetID(const std::string &id);
    CreatureType* SetDescription(const std::string &description);
    CreatureType* SetName(const std::string &name);
    CreatureType* SetSpritePos(const Vec2 &pos);
    CreatureType* SetSpriteColor(const Color &color);
    CreatureType* SetSpawnChance(int chance);
    CreatureType* SetDietType(DietType dietType);

private:
    std::string id;
    std::string name;
    std::string description;
    Vec2 spritePos;
    Color spriteColor;
    int spawnChance;
    DietType dietType;
};

class Creature {
private:
    const CreatureType &type;
    Vec3 pos;
    std::list<Vec3> path;

public:
    Creature(const CreatureType &type, Vec3 pos);

    [[nodiscard]] [[nodiscard]] const CreatureType& GetType() const;
    [[nodiscard]] [[nodiscard]] const Vec3& GetPosition() const;
    void SetPosition(Vec3 pos);
    std::optional<Vec3> Update(const World &world);
};
