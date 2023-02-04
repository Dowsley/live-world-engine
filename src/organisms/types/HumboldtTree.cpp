#include "HumboldtTree.h"

OrganismAction HumboldtTree::Spawn(World *world, int x, int y, int z)
{
	int treeHeight = 8;
	
	// Check if there is space for the tree to grow
	bool isInBounds = true;
	Tile *t;

	for (int currHeight = 0; currHeight <= treeHeight; currHeight++)
	{
		t = world->GetTile(x, y, z-currHeight);
		isInBounds = isInBounds && (t != nullptr);
		isInBounds = isInBounds && (t->type->GetName() == "empty");
		if (!isInBounds) {
			return OrganismAction::NOTHING;
		}
	}

	// Tree trunk
	for (int currHeight = 0; currHeight <= treeHeight; currHeight++)
	{
		_spawnInTile(world, trunk, x, y, z-currHeight);
	}

	// Leaves (3x3 cube centered on the top of the tree)
	bool spawned;
	for (int z_offset = -1; z_offset <= 1; z_offset++)
	{
		for (int y_offset = -1; y_offset <= 1; y_offset++)
		{
			for (int x_offset = -1; x_offset <= 1; x_offset++)
			{
				spawned = _spawnInTile(world, leaves, x+x_offset, y+y_offset, z-treeHeight+z_offset);
			}
		}
	}

	return OrganismAction::SPAWN;
};

OrganismAction HumboldtTree::Update(World *world)
{
	// Does something with the world and itself
	return OrganismAction::GROW;
};