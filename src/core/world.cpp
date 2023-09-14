#include "world.h"

#include <utility>

#include "settings.h"
#include "../creatures/creature.h"
#include "../utils/arithmetics.h"
#include "../utils/geometry.h"
#include "../lib/noise.cpp"

World::World(Vec3 dimensions)
: dimensions(dimensions), creatureManager(std::make_unique<CreatureManager>(this)),
map(new Tile[dimensions.GetFlattenedSize()]), tileRegistry(TileRegistry(Settings::TILE_REGISTRY_PATH)),
tileInstanceManager(std::make_unique<TileInstanceManager>(this))
{
    LoadData();
}

World::~World()
{
    delete[] map;
}

int World::GetHeight() const { return dimensions.height(); }
int World::GetWidth() const { return dimensions.width(); }
int World::GetDepth() const { return dimensions.depth(); }
const Vec3& World::GetDimensions() const { return dimensions; }
bool World::IsPositionEmpty(const Vec3 &pos) const
{
    bool isTypeEmpty = GetTypeIDForTileAt(pos) == "EMPTY";
    bool creatureThere = IsThereCreatureAt(pos);
    return isTypeEmpty && !creatureThere;
}

bool World::IsThereCreatureAt(const Vec3 &pos) const
{
    return (creatureManager->GetItemAt(pos) != nullptr);
}

std::tuple<Tile*, Creature*> World::_getTileAndCreature(const Vec3 &pos) const
{
    Tile *t = _getTile(pos);
    Creature *c = creatureManager->GetItemAt(pos);

    return std::make_tuple(t, c);
}

Tile* World::_getTile(const Vec3 &pos) const
{
    if (!_isInBounds(pos)) {
        return nullptr;
    }
    int flatIndex = GeometryUtils::Flatten3DCoords(pos, dimensions);
    return &map[flatIndex];
}
void World::_setTile(const Vec3 &pos, TileType *type)
{
    Tile *tile = _getTile(pos);
    if (!type) {
        throw std::runtime_error("Tile type at " + pos.ToString() + " is null");
    }
    
    tile->type = type;
    tile->spriteVariantIndex = tile->type->GetRandomSpriteIndex();
}

/* TODO: Implement this + review if this system is correct, because there are tile references that may need to be updated 
 * Thinking about it now... wouldnt it be better if I just swap the entire structs? */
void World::_swapTiles(Tile *tile1, Tile *tile2)
{
    // std::swap(tile1->type, tile2->type);
    // std::swap(tile1->defaultSpriteIndex, tile2->defaultSpriteIndex);
    // std::swap(tile1->defaultForeColorIndex, tile2->defaultForeColorIndex);
    // std::swap(tile1->defaultBackColorIndex, tile2->defaultBackColorIndex);
}

bool World::_isInBounds(const Vec3 &pos) const
{
    bool res = 
        (pos.x() < dimensions.width() && pos.x() >= 0)
        && (pos.y() < dimensions.height() && pos.y() >= 0)
        && (pos.z() < dimensions.depth() && pos.z() >= 0);
    return res;
}

const Vec2& World::GetTileSprite(const Vec3 &pos) const
{
    Tile *t;
    Creature *c;
    std::tie(t, c) = _getTileAndCreature(pos);
    
    if (c != nullptr && t->type->GetID() == "EMPTY") {
        return c->GetType()->GetSpritePos();
    }
    return tileInstanceManager->GetSprite(t).position;
}
const Color& World::GetTileColor(const Vec3 &pos) const
{
    Tile *t;
    Creature *c;
    std::tie(t, c) = _getTileAndCreature(pos);

    if (c != nullptr && t->type->GetID() == "EMPTY") {
        return c->GetType()->GetSpriteColor();
    }
    return tileInstanceManager->GetSprite(t).color;
}

TileType* World::GetTypeForTileAt(const Vec3 &pos) const
{
    Tile *t = _getTile(pos);
    if (!t) {
        return nullptr;
    }
    return t->type;
}
const std::string& World::GetTypeIDForTileAt(const Vec3 &pos) const
{
    Tile *t = _getTile(pos);
    return t->type->GetID();
}

const std::string& World::GetTypeIDForCreatureAt(const Vec3 &pos) const
{
    Creature *c = creatureManager->GetItemAt(pos);
    if (c == nullptr) {
        return "NONE";
    }
    return c->GetType()->GetID();
}

void World::LoadData()
{
    tileRegistry.Initialize();
}

void World::Update()
{
    creatureManager->UpdateCreatures();
}

void World::Generate()
{
    GenerateTestBiome();
}

void World::GenerateTestBiome()
{
    int flatIndex = 0;

    /* 1. Generate height map with noise */
    FastNoiseLite noise;
    noise.SetSeed(rand());
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noise.SetFractalType(FastNoiseLite::FractalType_FBm);
    std::vector<float> noiseData(dimensions.width() * dimensions.height());
    for (int y = 0; y < dimensions.height(); y++) {
        for (int x = 0; x < dimensions.width(); x++) {
            flatIndex = GeometryUtils::Flatten2DCoords(Vec2(x, y), dimensions);
            noiseData[flatIndex] = noise.GetNoise(static_cast<float>(x), static_cast<float>(y));
        }
    }


    /* 2. Fill in with blocks */
    tileInstanceManager->ClearInstances();

    const int SOIL_LAYER_DEPTH = 20;
    std::vector<bool> soilLevelData(dimensions.width() * dimensions.height(), false);
    TileType *tileType = nullptr;

    for (int y = 0; y < dimensions.height(); y++) {
        for (int x = 0; x < dimensions.width(); x++) {
            flatIndex = GeometryUtils::Flatten2DCoords(Vec2(x, y), dimensions);
            unsigned short inverseDepth = static_cast<unsigned short>(
                ArithmeticsUtils::Scale(
                    noiseData[flatIndex],
                    -1.0f, 1.0f, 0.0f, static_cast<float>(dimensions.depth())
                )
            );

            for (int z = 0; z < dimensions.depth(); z++) {
                if (z >= inverseDepth) {
                    tileType = tileRegistry.GetTypeById("ROCK");
                } else {
                    if (z > SOIL_LAYER_DEPTH) {
                        tileType = (z == SOIL_LAYER_DEPTH + 1) 
                            ? tileRegistry.GetTypeById("GRASS")
                            : tileRegistry.GetTypeById("SOIL");
                    } else {
                        tileType = tileRegistry.GetTypeById("EMPTY");
                        if (z == SOIL_LAYER_DEPTH) {
                            flatIndex = GeometryUtils::Flatten2DCoords(Vec2(x, y), dimensions);
                            soilLevelData[flatIndex] = true;
                        }
                    }
                }
                _setTile(Vec3(x, y, z), tileType);
            }
        }
    }
    
    /* 3. Spawn creatures from a cumulative-weighted chance pool */
    creatureManager->ClearCreatures();

    std::vector<const CreatureType*> allCreatureTypes = creatureManager->GetAllTypes();
    std::vector<std::pair<std::string, int>> spawnChancePool;

    const CreatureType *prevType = nullptr;
    int weight = 0;
    for (const auto & t : allCreatureTypes) {
        weight = t->GetSpawnChance();
        if (prevType != nullptr) {
            weight += prevType->GetSpawnChance();
        }
        spawnChancePool.emplace_back(t->GetID(), weight);
        prevType = t;
    }

    int totalWeight = spawnChancePool.back().second;
    const int noSpawnWeight = static_cast<int>(totalWeight / Settings::SPAWN_CHANCE - totalWeight); 
    totalWeight += noSpawnWeight;

    for (int y = 0; y < dimensions.height(); y++) {
        for (int x = 0; x < dimensions.width(); x++) {
            flatIndex = GeometryUtils::Flatten2DCoords(Vec2(x, y), dimensions);
            if (soilLevelData[flatIndex]) {
                int randomValue = rand() % totalWeight;

                if (randomValue < noSpawnWeight) {
                    continue;
                }

                randomValue -= noSpawnWeight;

                // Find the creature to spawn based on the adjusted random value
                int i = 0;
                while (randomValue >= spawnChancePool[i].second) {
                    i++;
                }

                creatureManager->InstanceCreature(spawnChancePool[i].first, Vec3(x, y, SOIL_LAYER_DEPTH));
            }
        }
    }

}
