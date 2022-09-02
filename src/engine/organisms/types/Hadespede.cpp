#include "Hadespede.h"

#include "../../tiles/tile.h"

OrganismAction Hadespede::Spawn(World *world, int x, int y, int z)
{
	Tile *t = world->GetTile(x, y, z);
	xPos = x;
	yPos = y;
	zPos = z;
	return _spawnInTile(world, hadespede, x, y, z) ? OrganismAction::SPAWN : OrganismAction::NOTHING;
};

OrganismAction Hadespede::Update(World *world)
{
	Tile *creatureTile = world->GetTile(xPos, yPos, zPos);
	int newX = xPos + _getRandomMovementOffset();
	int newY = yPos + _getRandomMovementOffset();
	bool couldMove = _moveToTile(world, creatureTile, newX, newY, zPos);
	if (couldMove) {
		xPos = newX;
		yPos = newY;
		return OrganismAction::MOVE;
	}
	return OrganismAction::NOTHING;
};

// Will output a number either 1, 0, or -1
int Hadespede::_getRandomMovementOffset()
{
	return -1 + (rand() % static_cast<int>(3));
};