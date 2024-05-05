#include "creature.h"
#include "pathfinding.h"

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
Creature::Creature(const CreatureType &type, Vec3 pos, World *worldRef)
    : type(type), pos(pos), worldRef(worldRef) {};

std::optional<Vec3> Creature::Update() {
    if (path.empty()) { // If there is no current path
        const int radius = 10; // Radius of 10 meters
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(-radius, radius);

        // Attempt to find a valid target position within a maximum of 100 tries
        Vec3 target;
        bool validTargetFound = false;
        for (int i = 0; i < 100 && !validTargetFound; ++i) {
            int dx = dist(gen);
            int dy = dist(gen);
            target = Vec3(pos.x() + dx, pos.y() + dy, pos.z());

            // Check if the selected position is both walkable and empty
            if (worldRef->IsPositionWalkable(target) && worldRef->IsPositionEmpty(target)) {
                validTargetFound = true;
            }
        }

        if (!validTargetFound) {
            return std::nullopt; // No valid target found after multiple tries
        }

        // Get path to the new target position
        path = Pathfinding::FindPath(worldRef, pos, target);
    }

    // Follow the path
    if (!path.empty()) {
        Vec3 nextStep = path.front();
        path.pop_front();
        SetPosition(nextStep); // Update creature's position
        return nextStep;
    }

    return std::nullopt; // No movement if path is somehow empty
}

const CreatureType& Creature::GetType() const { return type; }
const Vec3& Creature::GetPosition() const { return pos; }
void Creature::SetPosition(Vec3 pos) { this->pos = pos; }
