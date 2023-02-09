#ifndef HADESPEDE_H
#define HADESPEDE_H

#include <random>

#include "../organism.h"
#include "../../tiles/tile.h"
#include "../../tiles/functions.h"

class Hadespede : public Organism
{
private:
	int xPos, yPos, zPos;
	TileType *hadespede = BuildTileType("hadespede", 200)
		->AddDefaultSprite(Vec2(2, 14))
		->AddDefaultForeColor(255, 0, 255)
		->AddDefaultBackColor(0, 0, 0);

	int _getRandomMovementOffset();

public:
	OrganismAction Spawn(World *world, int x, int y, int z) override;
	OrganismAction Update(World *world) override;
};

#endif