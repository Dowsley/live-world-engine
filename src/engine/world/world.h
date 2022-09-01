#pragma once

#include <vector>

#include "../graphics/olcPixelGameEngine.h"

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

	olc::vi2d GetTileSprite(int x, int y, int z);
	olc::Pixel GetTileForeColor(int x, int y, int z);
	olc::Pixel GetTileBackColor(int x, int y, int z);
	void LogTileType(int x, int y, int z);

	void Update();

	void Generate();

	void GenerateTestBiome();
};
