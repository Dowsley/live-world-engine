#include "BoneRose.h"

#include "../../tiles/tile.h"

OrganismAction BoneRose::Spawn(World *world, int x, int y, int z)
{
	Tile *t = world->GetTile(x, y, z);
	xPos = x;
	yPos = y;
	zPos = z;
	return _spawnInTile(world, boneRose, x, y, z) ? OrganismAction::SPAWN : OrganismAction::NOTHING;
};

OrganismAction BoneRose::Update(World *world)
{
	return OrganismAction::NOTHING;
};
