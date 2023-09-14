#include "core/index.cpp"
#include "tiles/index.cpp"
#include "creatures/index.cpp"
#include "utils/index.cpp"
#include "structures/index.cpp"
#include "lib/index.cpp"
#include "lwe.cpp"

int main(int argc, char const *argv[])
{
    LiveWorldEngine game;

    game.Construct(
        Settings::TILE_SIZE.x * 26,
        Settings::TILE_SIZE.y * 17,
        4, 4
        );
    game.Start();

    return 0;
}