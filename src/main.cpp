#include "core/index.h"
#include "tiles/index.h"
#include "creatures/index.h"
#include "utils/index.h"
#include "structures/index.h"
#include "lib/index.h"
#include "lwe.h"

int main(int argc, char const *argv[])
{
    LiveWorldEngine game;

    game.Construct(
        Settings::TILE_SIZE.x * 26,
        Settings::TILE_SIZE.y * 17,
        4, 4, true
        );
    game.Start();

    return 0;
}
