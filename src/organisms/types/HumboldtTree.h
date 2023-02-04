#ifndef HUMBOLDT_TREE_H
#define HUMBOLDT_TREE_H

#include "../organism.h"
#include "../../tiles/tile.h"
#include "../../tiles/functions.h"

class HumboldtTree : public Organism
{
public:
	TileType *trunk = BuildTileType("trunk", 400)
		->AddDefaultSprite(olc::vi2d(15, 6))
        ->AddDefaultForeColor(128, 128, 0)
        ->AddDefaultBackColor(0, 0, 0);

	TileType *leaves = BuildTileType("leaves", 20)
		->AddDefaultSprite(olc::vi2d(12, 10))
		->AddDefaultSprite(olc::vi2d(11, 10))
        ->AddDefaultForeColor(0, 71, 0)
        ->AddDefaultBackColor(0, 0 ,0);

	OrganismAction Spawn(World *world, int x, int y, int z) override;
	OrganismAction Update(World *world) override;
};

#endif