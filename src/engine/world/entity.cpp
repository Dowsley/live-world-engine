#include "../graphics/olcPixelGameEngine.h"
#include "tile.cpp"

#include <string>
#include <vector>
#include <random>

class EntityType {
private:
    std::string name;
    std::vector<Tile> availableBlocks;

public:
    static EntityType *UNINITIALIZED;
    EntityType(std::string name)
    : name(name) {};

    std::string GetName() { return name; };
    Entity *CreateEntity()
    {
        return new Entity();
    }
};

EntityType *EntityType::UNINITIALIZED = new EntityType("uninitialized");

class Entity {
private:
    EntityType *type = EntityType::UNINITIALIZED;
    // unsigned short health;

public:
    Entity(EntityType *type)
    {
        this->type = type;
    }
};
