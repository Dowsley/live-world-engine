#ifndef BONE_ROSE_H
#define BONE_ROSE_H

#include "../organism.h"
#include "../../tiles/tile.h"
#include "../../tiles/functions.h"

class BoneRose : public Organism
{
private:
	int xPos, yPos, zPos;
	TileType *boneRose = BuildTileType("bone rose", 10)
		->AddDefaultSprite(olc::vi2d(7, 14))
		->AddDefaultForeColor(249, 246, 238)
		->AddDefaultForeColor(260, 246, 230)
		->AddDefaultBackColor(0, 0, 0);

public:
	OrganismAction Spawn(World *world, int x, int y, int z) override;
	OrganismAction Update(World *world) override;
};

#endif