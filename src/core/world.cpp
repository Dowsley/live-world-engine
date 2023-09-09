#include "world.h"

#include "../creatures/creature.h"

#include "../utils/arithmetics.h"
#include "../lib/noise.cpp"
#include "settings.h"

World::World(Vec3 dimensions)
: height(dimensions.x()), width(dimensions.y()), depth(dimensions.z()),
  totalSize(height * width * depth), creatureManager(std::make_unique<CreatureManager>(this)), map(new Tile[totalSize])
{}

World::~World()
{
    delete map;
}


int World::Flatten3DCoords(int x, int y, int z) { return y + height * (x + width * z); }
int World::Flatten2DCoords(int x, int y) { return y * width + x; }

int World::GetHeight() { return height; }
int World::GetWidth() { return width; }
int World::GetDepth() { return depth; }
void World::SetHeight(int height) { this->height = height; }
void World::SetWidth(int width) { this->width = width; }
void World::SetDepth(int depth) { this->depth = depth; }

bool World::IsThereCreatureAt(int x, int y, int z)
{
    return (creatureManager->GetCreatureAt(Vec3(x, y, z)) != nullptr);
}

std::tuple<Tile*, Creature*> World::_getTileAndCreature(Vec3 pos)
{
    Tile* t = GetTile(pos.x(), pos.y(), pos.z());
    Creature *c = creatureManager->GetCreatureAt(Vec3(pos.x(), pos.y(), pos.z()));

    return std::make_tuple(t, c);
}

Tile* World::GetTile(int x, int y, int z)
{
    if (!IsInBounds(x,y,z)) {
        return nullptr;
    }
    return &map[Flatten3DCoords(x, y, z)];
}
void World::SetTile(int x, int y, int z, TileType *type)
{
    Tile *tile = GetTile(x, y, z);
    if (!type) {
        printf("OK ENOUGH");
        throw std::runtime_error("Tile type of name " + tile->type->GetName() + " is null");
    }
    tileRegistry.SetupTile(tile, type);
}

void World::SwapTiles(Tile *tile1, Tile *tile2)
{
    std::swap(tile1->type, tile2->type);
    std::swap(tile1->metadata, tile2->metadata);
    std::swap(tile1->defaultSpriteIndex, tile2->defaultSpriteIndex);
    std::swap(tile1->defaultForeColorIndex, tile2->defaultForeColorIndex);
    std::swap(tile1->defaultBackColorIndex, tile2->defaultBackColorIndex);
}

bool World::IsInBounds(int x, int y, int z)
{
    bool res = (x < width && x >= 0) && (y < height && y >= 0) && (z < depth && z >= 0);
    return res;
}

Vec2 World::GetTileSprite(int x, int y, int z)
{
    Tile *t;
    Creature *c;
    std::tie(t, c) = _getTileAndCreature(Vec3(x, y, z));
    
    if (c != nullptr && t->type->GetName() == "empty") {
        return c->GetType()->GetSpritePos();
    }
    return tileRegistry.GetSprite(t);
}
Color World::GetTileForeColor(int x, int y, int z)
{
    Tile *t;
    Creature *c;
    std::tie(t, c) = _getTileAndCreature(Vec3(x, y, z));

    if (c != nullptr && t->type->GetName() == "empty") {
        return c->GetType()->GetSpriteColor();
    }
    return tileRegistry.GetForeColor(t);
}
Color World::GetTileBackColor(int x, int y, int z)
{
    Tile *t;
    Creature *c;
    std::tie(t, c) = _getTileAndCreature(Vec3(x, y, z));

    if (c != nullptr && t->type->GetName() == "empty") {
        return Settings::BACK_PLACEHOLDER;
    }
    return tileRegistry.GetBackColor(t);
}
TileType* World::GetTileType(int x, int y, int z)
{
    Tile *t = GetTile(x, y, z);
    if (!t) {
        return nullptr;
    }
    return t->type;
}
std::string World::GetTileTypeName(int x, int y, int z)
{
    Tile *t = GetTile(x, y, z);
    if (!t) {
        return "";
    }
    return t->type->GetName();
}

void World::LogTileType(int x, int y, int z)
{
    Tile *t = GetTile(x, y, z);
    if (!t) {
        printf("Tile POSITION %d %d %d does not exist, somehow\n", x, y, z);
        return;
    }
    if (!t) {
        printf("Tile TYPE type in %d %d %d does not exist, somehow\n", x, y, z);
        return;
    }
    printf("%d, %d, %d, Name: %s\n", x, y, z, t->type->GetName().c_str());
}

void World::Update()
{
    creatureManager->UpdateEntities();
}

void World::Generate()
{
    GenerateTestBiome();
}

void World::GenerateTestBiome()
{
    const int SOIL_LAYER_DEPTH = 20;
    const int MAX_SPAWN_CHANCE = 10000;

    FastNoiseLite noise;
    noise.SetSeed(rand());
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noise.SetFractalType(FastNoiseLite::FractalType_FBm);

    // Using std::vector is safer than raw arrays and manual memory management
    std::vector<float> noiseData(width * height);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            noiseData[Flatten2DCoords(x, y)] = noise.GetNoise(static_cast<float>(x), static_cast<float>(y));
        }
    }

    std::vector<bool> soilLevelData(width * height, false); // Initialization is in-built

    TileType* tileType = nullptr;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned short inverseDepth = static_cast<unsigned short>(
                ArithmeticsUtils::Scale(
                    noiseData[Flatten2DCoords(x, y)],
                    -1.0f, 1.0f, 0.0f, static_cast<float>(depth)
                )
            );

            for (int z = 0; z < depth; z++) {
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
                            soilLevelData[y * width + x] = true;
                        }
                    }
                }
                SetTile(x, y, z, tileType);
            }
        }
    }

    int crabSpawnChance = creatureManager->GetTypeById("CRAB")->GetSpawnChance();
    int rattlesnakeSpawnChance = creatureManager->GetTypeById("RATTLESNAKE")->GetSpawnChance();

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (soilLevelData[y * width + x]) {
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
