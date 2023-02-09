#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "../engine/olcPixelGameEngine.h"
#include "../structures/color.h"
#include "../structures/vec2.h"

class TileType;
class TileManager;
class Tile;
class Organism;
class FastNoiseLite;

class World
{
private:
	// Utils
	int height;
	int width;
	int depth;
	int totalSize;
	FastNoiseLite *noise;

	// Content managers
	TileManager *tileManager;

	// Stage
	std::vector<Organism*> organisms;
	Tile *map;

public:
	World(int width, int height, int depth);

	~World();

	int Transform3DCoords(int x, int y, int z);
	int Transform2DCoords(int x, int y);

	int GetHeight();
	int GetWidth();
	int GetDepth();
	void SetHeight(int height);
	void SetWidth(int width);
	void SetDepth(int depth);

	Tile *GetTile(int x, int y, int z);
	void SetTile(int x, int y, int z, TileType *type, Organism *organism);
	void SetTile(int x, int y, int z, TileType *type);
	void SwapTiles(Tile *tile1, Tile *tile2);
	bool IsInBounds(int x, int y, int z);

	Vec2 GetTileSprite(int x, int y, int z);
	Color GetTileForeColor(int x, int y, int z);
	Color GetTileBackColor(int x, int y, int z);
	TileType *GetTileType(int x, int y, int z);
	std::string GetTileTypeName(int x, int y, int z);
	void LogTileType(int x, int y, int z);

	void Update();

	void Generate();

	void GenerateTestBiome();
};

#endif