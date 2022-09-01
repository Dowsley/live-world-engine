#include "organism.h"
#include "../tiles/tile.h"

bool Organism::_spawnInTile(World *world, TileType *type, int x, int y, int z)
{
	Tile *target = world->GetTile(x, y, z);
	if (!target) {
		// if (type->GetName() == "leaves") {
		// 	world->LogTileType(x, y, z);
		// }
		return false;
	}

	if (target->type->GetName() != "empty") {
		// if (type->GetName() == "leaves") {
		// 	world->LogTileType(x, y, z);
		// }
		return false;
	}

	world->SetTile(x, y, z, type, this);
	return true;
};

bool Organism::_growToTile(World *world, TileType *type, int x, int y, int z)
{
	Tile *target = world->GetTile(x, y, z);
	if (!target) 
		return false;
	if (target->type->GetName() != "empty")
		return false;

	world->SetTile(x, y, z, type, this);
	return true;
};

bool Organism::_moveToTile(World *world, Tile *tile, int x, int y, int z)
{
	Tile *target = world->GetTile(x, y, z);
	if (!target)
		return false;
	if (target->type->GetName() != "empty")
		return false;

	world->SwapTiles(tile, target);
	return true;
};