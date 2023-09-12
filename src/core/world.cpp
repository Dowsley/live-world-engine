#include "world.h"

#include "settings.h"
#include "../creatures/creature.h"
#include "../utils/arithmetics.h"
#include "../utils/geometry.h"
#include "../lib/noise.cpp"

World::World(Vec3 dimensions)
: dimensions(dimensions), creatureManager(std::make_unique<CreatureManager>(this)), map(new Tile[dimensions.GetFlattenedSize()])
{}

World::~World()
{
    delete[] map;
}

int World::GetHeight() const { return dimensions.height(); }
int World::GetWidth() const { return dimensions.width(); }
int World::GetDepth() const { return dimensions.depth(); }
const Vec3& World::GetDimensions() const { return dimensions; }

bool World::IsThereCreatureAt(const Vec3 &pos) const
{
    return (creatureManager->GetCreatureAt(pos) != nullptr);
}

std::tuple<Tile*, Creature*> World::_getTileAndCreature(const Vec3 &pos) const
{
    Tile *t = _getTile(pos);
    Creature *c = creatureManager->GetCreatureAt(pos);

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
        printf("OK ENOUGH");
        throw std::runtime_error("Tile type of name " + tile->type->GetName() + " is null");
    }
    tileRegistry.SetupTile(tile, type);
}

void World::_swapTiles(Tile *tile1, Tile *tile2)
{
    std::swap(tile1->type, tile2->type);
    std::swap(tile1->metadata, tile2->metadata);
    std::swap(tile1->defaultSpriteIndex, tile2->defaultSpriteIndex);
    std::swap(tile1->defaultForeColorIndex, tile2->defaultForeColorIndex);
    std::swap(tile1->defaultBackColorIndex, tile2->defaultBackColorIndex);
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
    
    if (c != nullptr && t->type->GetName() == "empty") {
        return c->GetType()->GetSpritePos();
    }
    return tileRegistry.GetSprite(t);
}
const Color& World::GetTileForeColor(const Vec3 &pos) const
{
    Tile *t;
    Creature *c;
    std::tie(t, c) = _getTileAndCreature(pos);

    if (c != nullptr && t->type->GetName() == "empty") {
        return c->GetType()->GetSpriteColor();
    }
    return tileRegistry.GetForeColor(t);
}
const Color& World::GetTileBackColor(const Vec3 &pos) const
{
    Tile *t;
    Creature *c;
    std::tie(t, c) = _getTileAndCreature(pos);

    if (c != nullptr && t->type->GetName() == "empty") {
        return Settings::BACK_PLACEHOLDER;
    }
    return tileRegistry.GetBackColor(t);
}
TileType* World::GetTileType(const Vec3 &pos) const
{
    Tile *t = _getTile(pos);
    if (!t) {
        return nullptr;
    }
    return t->type;
}
std::string World::GetTileTypeName(const Vec3 &pos) const
{
    Tile *t = _getTile(pos);
    if (!t) {
        return "";
    }
    return t->type->GetName();
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

    const int SOIL_LAYER_DEPTH = 20;
    const int MAX_SPAWN_CHANCE = 10000;

    FastNoiseLite noise;
    noise.SetSeed(rand());
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noise.SetFractalType(FastNoiseLite::FractalType_FBm);

    // Using std::vector is safer than raw arrays and manual memory management
    std::vector<float> noiseData(dimensions.width() * dimensions.height());
    for (int y = 0; y < dimensions.height(); y++) {
        for (int x = 0; x < dimensions.width(); x++) {
            flatIndex = GeometryUtils::Flatten2DCoords(Vec2(x, y), dimensions);
            noiseData[flatIndex] = noise.GetNoise(static_cast<float>(x), static_cast<float>(y));
        }
    }

    std::vector<bool> soilLevelData(dimensions.width() * dimensions.height(), false); // Initialization is in-built

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
                    tileType = tileRegistry.GetNaturalTileType("rock");
                } else {
                    if (z > SOIL_LAYER_DEPTH) {
                        tileType = (z == SOIL_LAYER_DEPTH + 1) 
                            ? tileRegistry.GetNaturalTileType("grass")
                            : tileRegistry.GetNaturalTileType("soil");
                    } else {
                        tileType = tileRegistry.GetNaturalTileType("empty");
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
    
    creatureManager->ClearCreatures();
    int crabSpawnChance = creatureManager->GetTypeById("CRAB")->GetSpawnChance();
    int rattlesnakeSpawnChance = creatureManager->GetTypeById("RATTLESNAKE")->GetSpawnChance();

    for (int y = 0; y < dimensions.height(); y++) {
        for (int x = 0; x < dimensions.width(); x++) {
            flatIndex = GeometryUtils::Flatten2DCoords(Vec2(x, y), dimensions);
            if (soilLevelData[flatIndex]) {
                int spawnRand = rand() % MAX_SPAWN_CHANCE;
                if (spawnRand < crabSpawnChance) {
                    creatureManager->InstanceCreature("CRAB", Vec3(x, y, SOIL_LAYER_DEPTH));
                } else if (spawnRand < rattlesnakeSpawnChance) {
                    creatureManager->InstanceCreature("RATTLESNAKE", Vec3(x, y, SOIL_LAYER_DEPTH));
                }
            }
        }
    }
}
