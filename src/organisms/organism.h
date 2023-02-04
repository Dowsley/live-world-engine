#ifndef ORGANISM_H
#define ORGANISM_H

#include <vector>

#include "../core/world.h"

class Tile;

enum class OrganismAction
{
	MOVE,
	GROW,
	INTERNAL,
	SPAWN,
	NOTHING
};

class Organism
{
protected:
	bool _spawnInTile(World *world, TileType *type, int x, int y, int z);
	bool _growToTile(World *world, TileType *type, int x, int y, int z);
	bool _moveToTile(World *world, Tile *tile, int x, int y, int z);

public:
	virtual OrganismAction Spawn(World *world, int x, int y, int z) = 0;
	virtual OrganismAction Update(World *world) = 0;
};

#endif