#ifndef HUMBOLDT_TREE_H
#define HUMBOLDT_TREE_H

#include "../organism.h"
#include "../../tiles/tile.h"
#include "../../tiles/functions.h"

class HumboldtTree : public Organism
{
public:
	TileType *trunk = BuildTileType("trunk", 400)
		->AddDefaultSprite(Vec2(4, 7))
        ->AddDefaultForeColor(128, 128, 0)
        ->AddDefaultBackColor(0, 0, 0);

	TileType *leaves = BuildTileType("leaves", 20)
		->AddDefaultSprite(Vec2(0, 7))
		->AddDefaultSprite(Vec2(1, 7))
		->AddDefaultSprite(Vec2(2, 7))
		->AddDefaultSprite(Vec2(3, 7))
        ->AddDefaultForeColor(0, 71, 0)
        ->AddDefaultBackColor(0, 0 ,0);

	OrganismAction Spawn(World *world, int x, int y, int z) override;
	OrganismAction Update(World *world) override;
};

#endif