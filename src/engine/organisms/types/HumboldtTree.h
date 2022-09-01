#pragma once

#include <random>

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

// // ANIMAL: Red centipede, the size of a small dog. Likes to crawl next to tree roots.
// class Hadespede : public Organism
// {
// private:
// 	TileType *boneRose = BuildTileType("tumble raptor", 200)
// 		->AddDefaultSprite(olc::vi2d(2, 2))
// 		->AddDefaultForeColor(0x000AA0FF)
// 		->AddDefaultBackColor(0x00000000);

// public:
// 	OrganismAction Spawn(World *world, int x, int y, int z) override;
// 	OrganismAction Update(World *world) override;
// };

// // SMALL PLANT: Grows where tree roots are prevalent.
// class BoneRose : public Organism
// {
// private:
// 	TileType *boneRose = BuildTileType("bone rose", 10)
// 		->AddDefaultSprite(olc::vi2d(2, 2))
// 		->AddDefaultForeColor(0x000AA0FF)
// 		->AddDefaultForeColor(0x0AA000FF)
// 		->AddDefaultForeColor(0xAA0AAAFF)
// 		->AddDefaultBackColor(0x00000000);

// public:
// 	OrganismAction Spawn(World *world, int x, int y, int z) override;
// 	OrganismAction Update(World *world) override;
// };
