#ifndef BONE_ROSE_H
#define BONE_ROSE_H

#include "../organism.h"
#include "../../tiles/tile.h"
#include "../../tiles/functions.h"

class BoneRose : public Organism
{
private:
	TileType *boneRose = BuildTileType("bone rose", 10)
		->AddDefaultSprite(olc::vi2d(2, 2))
		->AddDefaultForeColor(0x000AA0FF)
		->AddDefaultForeColor(0x0AA000FF)
		->AddDefaultForeColor(0xAA0AAAFF)
		->AddDefaultBackColor(0x00000000);

public:
	OrganismAction Spawn(World *world, int x, int y, int z) override;
	OrganismAction Update(World *world) override;
};

#endif