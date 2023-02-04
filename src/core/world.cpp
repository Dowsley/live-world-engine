#include "world.h"

#include "../tiles/manager.h"
#include "../organisms/organism.h"

#include "../organisms/types/index.h"
#include "../util/arithmetics.h"
#include "../util/noise.cpp"

World::World(int width, int height, int depth)
{
	this->height = height;
	this->width = width;
	this->depth = depth;
	this->totalSize = height * width * depth;

	noise = new FastNoiseLite();
	tileManager = new TileManager();
	map = (Tile *)malloc(sizeof(Tile) * totalSize);
}

World::~World()
{
	free(noise);
	free(tileManager);
	free(map);
}

int World::Transform3DCoords(int x, int y, int z) { return y + height * (x + width * z); }
int World::Transform2DCoords(int x, int y) { return y * width + x; }

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
	return &map[Transform3DCoords(x, y, z)];
}
void World::SetTile(int x, int y, int z, TileType *type, Organism *organism)
{
	Tile *tile = GetTile(x, y, z);
	if (!type) {
		printf("OK ENOUGH");
		exit(0);
	}
	tileManager->SetupTile(tile, type, organism);
}
void World::SetTile(int x, int y, int z, TileType *type)
{
	Tile *tile = GetTile(x, y, z);
	if (!type) {
		printf("OK ENOUGH");
		exit(0);
	}
	tileManager->SetupTile(tile, type, nullptr);
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

olc::vi2d World::GetTileSprite(int x, int y, int z)
{
	Tile *t = GetTile(x, y, z);
	olc::vi2d res = tileManager->GetSprite(t);
	return res;
}
olc::Pixel World::GetTileForeColor(int x, int y, int z)
{
	Tile *t = GetTile(x, y, z);
	olc::Pixel res = tileManager->GetForeColor(t);
	return res;
}
olc::Pixel World::GetTileBackColor(int x, int y, int z)
{
	Tile *t = GetTile(x, y, z);
	olc::Pixel res = tileManager->GetBackColor(t);
	return res;
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
	for (auto & o : organisms)
	{
		o->Update(this);
	}
}

void World::Generate()
{
	GenerateTestBiome();
}

void World::GenerateTestBiome()
{
	int SAND_LAYER_DEPTH = 20;

	noise->SetSeed(rand());

	// Create and configure FastNoise object
	noise->SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
	// noise->SetNoiseType(FastNoiseLite::NoiseType_Cellular);

	// noise->SetFrequency(0.01f);

	noise->SetFractalType(FastNoiseLite::FractalType_FBm);
	// noise->SetFractalType(FastNoiseLite::FractalType_Ridged);
	// noise->SetFractalType(FastNoiseLite::FractalType_PingPong);

	// Gather noise data
	float *noiseData = new float[width * height];
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			noiseData[y * width + x] = noise->GetNoise((float)x, (float)y);
		}
	}
	
	unsigned short inverseDepth;
	bool *sandLevelData = new bool[width * height];
	memset(sandLevelData, false, width * height);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			inverseDepth = (unsigned short)Arithmetics::scale(
				noiseData[y * width + x],
				-1.0f,
				1.0,
				0.0f,
				(float)depth);
			
			for (int z = 0; z < depth; z++)
			{
				if (z >= inverseDepth)
				{
					SetTile(x, y, z, tileManager->GetNaturalTileType("rock"));
				}
				else
				{
					if (z > SAND_LAYER_DEPTH)
					{
						SetTile(x, y, z, tileManager->GetNaturalTileType("soil"));
					}
					else
					{
						SetTile(x, y, z, tileManager->GetNaturalTileType("empty"));
						if (z == SAND_LAYER_DEPTH) {
							sandLevelData[y * width + x] = true;
						}
					}
				}
			}
		}
	}
	
	// Organisms
	HumboldtTree *t;
	Hadespede *h;
	BoneRose *b;
	float treeSpawnChance = 20;
	float hadespedeSpawnChance = 5;
	float boneRoseSpawnChance = 20;
	bool spawned;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (sandLevelData[y * width + x])
			{
				if ((rand() % 10000) < treeSpawnChance)
				{
					t = new HumboldtTree();
					spawned = t->Spawn(this, x, y, SAND_LAYER_DEPTH) == OrganismAction::SPAWN;
					if (spawned) {
						organisms.push_back(t);
					} else {
						free(t);
					}
				}
				if ((rand() % 10000) < hadespedeSpawnChance)
				{
					h = new Hadespede();
					spawned = h->Spawn(this, x, y, SAND_LAYER_DEPTH) == OrganismAction::SPAWN;
					if (spawned) {
						organisms.push_back(h);
					} else {
						free(h);
					}
				}
				if ((rand() % 10000) < boneRoseSpawnChance)
				{
					b = new BoneRose();
					spawned = b->Spawn(this, x, y, SAND_LAYER_DEPTH) == OrganismAction::SPAWN;
					if (spawned) {
						organisms.push_back(b);
					} else {
						free(b);
					}
				}
			}
		}
	}

	delete[] noiseData;
	delete[] sandLevelData;
}