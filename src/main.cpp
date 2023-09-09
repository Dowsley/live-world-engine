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

    game.Construct(312, 204, 4, 4);
    game.Start();

    return 0;
}