#include "world.h"

#include "../creatures/creature.h"

#include "../utils/arithmetics.h"
#include "../lib/noise.cpp"
#include "settings.h"

World::World(Vec3 dimensions)
{
    this->height = dimensions.x();
    this->width = dimensions.y();
    this->depth = dimensions.z();
    this->totalSize = height * width * depth;

    map = (Tile *)malloc(sizeof(Tile) * totalSize);

    const int MAX_ENTITIES_PER_OCTANT = 10;  // Arbitrary number, adjust as needed
    Vec3 worldOrigin(width / 2, height, depth / 2);
    int worldSize = std::max({width, height, depth});
    creatureManager = new CreatureManager(this);
}

World::~World()
{
    delete map;
    delete creatureManager;
}

bool World::IsThereCreatureAt(int x, int y, int z)
{
    return creatureManager->GetCreatureAt(Vec3(x, y, z));
}
int World::Flatten3DCoords(int x, int y, int z) { return y + height * (x + width * z); }
int World::Flatten2DCoords(int x, int y) { return y * width + x; }

int World::GetHeight() { return height; }
int World::GetWidth() { return width; }
int World::GetDepth() { return depth; }
void World::SetHeight(int height) { this->height = height; }
void World::SetWidth(int width) { this->width = width; }
void World::SetDepth(int depth) { this->depth = depth; }

Tile *World::GetTile(int x, int y, int z)
{
    if (!IsInBounds(x,y,z))
        return nullptr;
    return &map[Flatten3DCoords(x, y, z)];
}
void World::SetTile(int x, int y, int z, TileType *type)
{
    Tile *tile = GetTile(x, y, z);
    if (!type) {
        printf("OK ENOUGH");
        exit(0);
    }
    tileRegistry.SetupTile(tile, type);
}

void World::SwapTiles(Tile *tile1, Tile *tile2)
{
    // Oh god.
    TileType *type1 = tile1->type;
    TileMetadata *metadata1 = tile1->metadata;
    unsigned char defaultSpriteIndex1 = tile1->defaultSpriteIndex;
    unsigned char defaultForeColorIndex1 = tile1->defaultForeColorIndex;
    unsigned char defaultBackColorIndex1 = tile1->defaultBackColorIndex;

    tile1->type = tile2->type;
    tile1->defaultSpriteIndex = tile2->defaultSpriteIndex;
    tile1->defaultForeColorIndex = tile2->defaultForeColorIndex;
    tile1->defaultBackColorIndex = tile2->defaultBackColorIndex;

    tile2->type = type1;
    tile2->defaultSpriteIndex = defaultSpriteIndex1;
    tile2->defaultForeColorIndex = defaultForeColorIndex1;
    tile2->defaultBackColorIndex = defaultBackColorIndex1;
}

bool World::IsInBounds(int x, int y, int z)
{
    bool res = (x < width && x >= 0) && (y < height && y >= 0) && (z < depth && z >= 0);
    return res;
}

Vec2 World::GetTileSprite(int x, int y, int z)
{
    // TODO: Stop repeating this behaviour
    Tile *t = GetTile(x, y, z);
    Creature *c = creatureManager->GetCreatureAt(Vec3(x, y, z));
    if (c != nullptr && t->type->GetName() == "empty") {
        return c->GetType()->GetSpritePos();
    }
    return tileRegistry.GetSprite(t);
}
Color World::GetTileForeColor(int x, int y, int z)
{
    // TODO: Stop repeating this behaviour
    Tile *t = GetTile(x, y, z);
    Creature *c = creatureManager->GetCreatureAt(Vec3(x, y, z));
    if (c != nullptr && t->type->GetName() == "empty") {
        return c->GetType()->GetSpriteColor();
    }
    return tileRegistry.GetForeColor(t);
}
Color World::GetTileBackColor(int x, int y, int z)
{
    // TODO: Stop repeating this behaviour
    Tile *t = GetTile(x, y, z);
    Creature *c = creatureManager->GetCreatureAt(Vec3(x, y, z));
    if (c != nullptr && t->type->GetName() == "empty") {
        return Settings::BACK_PLACEHOLDER;
    }
    return tileRegistry.GetBackColor(t);
}
TileType *World::GetTileType(int x, int y, int z)
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
    int SOIL_LAYER_DEPTH = 20;

    FastNoiseLite noise;

    noise.SetSeed(rand());

    // Create and configure FastNoise object
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    // noise->SetNoiseType(FastNoiseLite::NoiseType_Cellular);

    // noise->SetFrequency(0.01f);

    noise.SetFractalType(FastNoiseLite::FractalType_FBm);
    // noise->SetFractalType(FastNoiseLite::FractalType_Ridged);
    // noise->SetFractalType(FastNoiseLite::FractalType_PingPong);

    // Gather noise data
    float *noiseData = new float[width * height];
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            noiseData[Flatten2DCoords(x, y)] = noise.GetNoise((float)x, (float)y);
        }
    }
    
    bool *soilLevelData = new bool[width * height];
    memset(soilLevelData, false, width * height);

    TileType *tileType = nullptr;
    unsigned short inverseDepth = 0;
    int flattened2DCoords = 0;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            flattened2DCoords = Flatten2DCoords(x, y);
            inverseDepth = (unsigned short)ArithmeticsUtils::Scale(
                noiseData[flattened2DCoords],
                -1.0f,
                1.0,
                0.0f,
                (float)depth
            );
            
            for (int z = 0; z < depth; z++)
            {
                if (z >= inverseDepth) {
                    tileType = tileRegistry.GetNaturalTileType("rock");
                } else {
                    if (z > SOIL_LAYER_DEPTH) {
                        if (z == SOIL_LAYER_DEPTH + 1) {
                            tileType = tileRegistry.GetNaturalTileType("grass");
                        }
                        else {
                            tileType = tileRegistry.GetNaturalTileType("soil");
                        }
                    } else {
                        tileType = tileRegistry.GetNaturalTileType("empty");
                        if (z == SOIL_LAYER_DEPTH) {
                            soilLevelData[flattened2DCoords] = true;
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
                if ((rand() % 10000) < crabSpawnChance) {
                    creatureManager->InstanceCreature("CRAB", Vec3(x, y, SOIL_LAYER_DEPTH));	
                } else if ((rand() % 10000) < rattlesnakeSpawnChance) {
                    creatureManager->InstanceCreature("RATTLESNAKE", Vec3(x, y, SOIL_LAYER_DEPTH));
                }
            }
        }
    }


    delete[] noiseData;
    delete[] soilLevelData;
}
