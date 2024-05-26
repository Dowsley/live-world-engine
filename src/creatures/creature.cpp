#include "creature.h"
#include "pathfinding.h"

/* ---- CREATURE TYPE ---- */
const std::string& CreatureType::GetID() const { return id; }

const std::string& CreatureType::GetDescription() const { return description; }
const std::string& CreatureType::GetName() const { return name; }
const Vec2& CreatureType::GetSpritePos() const { return spritePos; }
const Color& CreatureType::GetSpriteColor() const { return spriteColor; }
int CreatureType::GetSpawnChance() const { return spawnChance; }
DietType CreatureType::GetDietType() const { return dietType; }

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

CreatureType* CreatureType::SetDietType(DietType dietType) {
    this->dietType = dietType;
    return this;
}

/* ---- CREATURE ---- */
Creature::Creature(const CreatureType &type, Vec3 pos)
    : type(type), pos(pos) {};

std::optional<Vec3> Creature::Update(const World &world) {
    if (path.empty()) { // If there is no current path
        const int LINE_OF_SIGHT_RADIUS = 15;
        if (GetType().GetDietType() == DietType::CARNIVORE) {
            // Hunt
            Vec3 target;
            bool validTargetFound = false;
            for (int i = -LINE_OF_SIGHT_RADIUS; i <= LINE_OF_SIGHT_RADIUS && !validTargetFound; ++i) {
                for (int j = -LINE_OF_SIGHT_RADIUS; j <= LINE_OF_SIGHT_RADIUS && !validTargetFound; ++j) {
                    for (int k = -LINE_OF_SIGHT_RADIUS; k <= LINE_OF_SIGHT_RADIUS && !validTargetFound; ++k) {
                        // Skip checking the starting position itself
                        if (i == 0 && j == 0 && k == 0) continue;

                        target.SetX(pos.x() + i);
                        target.SetY(pos.y() + j);
                        target.SetZ(pos.z() + k);

                        if (world.IsThereCreatureAt(target)) {
                            validTargetFound = true;
                        }
                    }
                }
            }

            if (!validTargetFound) {
                return std::nullopt;
            }

            // Get path to an adjacent position of the target
            Vec3 newTarget = target;
            validTargetFound = false;
            for (int i = -1; i <= 1 && !validTargetFound; ++i) {
                for (int j = -1; j <= 1 && !validTargetFound; ++j) {
                    for (int k = -1; k <= 1 && !validTargetFound; ++k) {
                        if (i == 0 && j == 0 && k == 0) continue;
                        newTarget.SetX(target.x() + i);
                        newTarget.SetY(target.y() + j);
                        newTarget.SetZ(target.z() + k);
                        if (world.IsPositionWalkable(newTarget)) {
                            validTargetFound = true;
                        }
                    }
                }
            }
            path = Pathfinding::FindPath(world, pos, newTarget);
        } else {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(-LINE_OF_SIGHT_RADIUS, LINE_OF_SIGHT_RADIUS);

            // Attempt to find a valid target position within a maximum of 100 tries
            Vec3 target;
            bool validTargetFound = false;
            for (int i = 0; i < 100 && !validTargetFound; ++i) {
                int dx = dist(gen);
                int dy = dist(gen);
                target = Vec3(pos.x() + dx, pos.y() + dy, pos.z());

                // Check if the selected position is both walkable and empty
                if (world.IsPositionWalkable(target) && world.IsPositionEmpty(target)) {
                    validTargetFound = true;
                }
            }

            if (!validTargetFound) {
                return std::nullopt; // No valid target found after multiple tries
            }

            // Get path to the new target position
            path = Pathfinding::FindPath(world, pos, target);
        }
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
