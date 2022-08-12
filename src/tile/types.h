#include "../../engine/olcPixelGameEngine.h"

class RedSand : public Tile {
public:
    RedSand()
    {

    }

    int Update() override
    {
        return 0;
    }

    olc::vi2d GetRepresentation() override
    {
        return olc::vi2d(13, 12);
    }

    olc::Pixel GetColor() override
    {
        return olc::YELLOW;
    }
};


class Rock : public Tile {
public:
    Rock()
    {

    }

    int Update() override
    {
        return 0;
    }

    olc::vi2d GetRepresentation() override
    {
        return olc::vi2d(13, 12);
    }

    olc::Pixel GetColor() override
    {
        return olc::YELLOW;
    }
};
